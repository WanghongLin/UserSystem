//
// Created by Wanghong Lin on 2019/10/23.
//

#ifndef USERSYSTEM_MYSQLDBCONNECTOR_H
#define USERSYSTEM_MYSQLDBCONNECTOR_H

#include "AbstractDbConnector.h"
#include "mysqlx/xdevapi.h"
#include "Utils.h"

static constexpr auto DB_NAME = "usersystem";
static constexpr auto TABLE_USER = "tbl_user";
static constexpr auto TABLE_USER_LOGIN_HISTORY = "tbl_user_login_history";

class MySQLDbConnector : public AbstractDbConnector {

public:
    explicit MySQLDbConnector(const std::string& url = "mysqlx://root@127.0.0.1") : _session(mysqlx::Session(url)) {}

    ~MySQLDbConnector() override {
        _session.commit();
        _session.close();
    }

    usersystem::UserModel CreateUser(const usersystem::UserModel &from) override;

    usersystem::ResponseCode UpdateUser(const usersystem::UserModel &from) override;

    usersystem::UserModel FetchUser(const std::string &username) override;

    usersystem::ResponseCode RemoveUser(const std::string &username) override;

    usersystem::UserLoginHistoryModel CreateLoginHistory(const usersystem::UserLoginHistoryModel &from) override;

    usersystem::ResponseCode UpdateLoginHistory(const usersystem::UserLoginHistoryModel &from) override;

    usersystem::UserLoginHistoryModel FetchLoginHistory(const std::string &username) override;

    usersystem::ResponseCode RemoveUserLoginHistory(const std::string &historyId) override;

private:
    mysqlx::Session _session;

    template<typename T> T create(const std::string& collection, const T& from) {
        try {
            auto schema = _session.createSchema(DB_NAME, true);
            auto collections = schema.createCollection(collection, true);

            auto jsonString = Utils::ToJsonString(from);
            auto result = collections.add(jsonString).execute();

            T ret;
            ret.CopyFrom(from);
            ret.set_id(*result.getGeneratedIds().begin());
            return ret;
        } catch (const mysqlx::Error& error) {
            std::cerr << "Error: " << error.what() << std::endl;
        } catch (std::exception& ex) {
            std::cerr << "Exception: " << ex.what() << std::endl;
        } catch (const char* ex) {
            std::cerr << ex << std::endl;
        }

        return T();
    }
};


#endif //USERSYSTEM_MYSQLDBCONNECTOR_H
