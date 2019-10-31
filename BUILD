load("@rules_cc//cc:defs.bzl", "cc_binary")


cc_library(
	name = "mysqlcpp",
	# or use -Lxxx -lstatic.a option in cc_binary linkopts to link to static library
	srcs = select({
		"@bazel_tools//src/conditions:darwin": ["mysqlcppconn_prebuilt/lib64/libmysqlcppconn8.dylib"],
		"@bazel_tools//src/conditions:linux_x86_64": ["mysqlcppconn_prebuilt/lib64/libmysqlcppconn8.so"],
		"//conditions:default": ["mysqlcppconn_prebuilt/lib64/libmysqlcppconn8.so"]
		}
	       ),
	hdrs = glob(["mysqlcppconn_prebuilt/include/**/*.h"]),
	includes = ["mysqlcppconn_prebuilt/include"],
    visibility = ["//visibility:public"]
    )

cc_library(
    name = "grpc_prebuilt",
	# or use -Lxxx -lstatic.a option in cc_binary linkopts to link to static library
    srcs = select({
		"@bazel_tools//src/conditions:darwin": ["grpc_prebuilt/lib/libgrpc++.dylib", "grpc_prebuilt/lib/libprotobuf.dylib"],
		#"@bazel_tools//src/conditions:linux_x86_64": ["/usr/local/lib/libgrpc++.so"],
		"//conditions:default": glob(["grpc_prebuilt/lib/*.dylib"])
    }),
    hdrs = glob(["grpc_prebuilt/include/**"]),
    includes = ["grpc_prebuilt/include"],
    visibility = ["//visibility:public"]
    )

cc_binary(
	name = "server",
	srcs = glob(["common/*.cc", "common/*.h", "server/*.cpp", "server/**/*.h"]),
	#copts = [ "-Iserver", "-Icommon", "-Iexternal/pb/include", "-Iexternal/grpc/include", "-Iexternal/mysql/include", "-Iexternal/ssl/include", "-Imysql-connector-cpp/build/out/include",
	#],
	#linkopts = [
	#	"-Lmysql-connector-cpp/build/out/lib64 -lmysqlcppconn8",
	#	"-L/Users/wanghonglin/Developments/Homebrew/Cellar/grpc/1.23.0_3/lib -lgrpc++",
	#	"-L/Users/wanghonglin/Developments/github/grpc/third_party/protobuf/out/lib -lprotobuf",
	#	"-L/Users/wanghonglin/Developments/Homebrew/opt/openssl/lib -lssl -lcrypto"],
	#deps = ["@pb//:pbh", "@grpc//:grpch", "@mysql//:mysqlh", "@ssl//:sslh", ":mysqlcpp", "@local_config_brew//:brew_library"],
	copts = [ "-Iserver", "-Icommon" ],
	includes = ["common", "server"],
	linkopts = [
		"-Lmysqlcppconn_prebuilt/lib64 -lmysqlcppconn8",
		"-Lgrpc_prebuilt/lib -L/usr/local/lib -lgrpc++", "-lprotobuf", "-lssl -lcrypto"],
	deps = select({
	    "@bazel_tools//src/conditions:darwin": [":mysqlcpp", ":grpc_prebuilt", "@local_config_brew//:brew_library"],
	    "@bazel_tools//src/conditions:linux_x86_64": [":mysqlcpp"],
		"//conditions:default": [":mysqlcpp", ":grpc_prebuilt", "@local_config_brew//:brew_library"],
	}),
	)
