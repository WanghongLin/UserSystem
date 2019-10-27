// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: usersystem.proto

package com.wanghong.grpc.usersystem.proto;

public interface UserModelOrBuilder extends
    // @@protoc_insertion_point(interface_extends:usersystem.UserModel)
    com.google.protobuf.MessageLiteOrBuilder {

  /**
   * <code>required string id = 1;</code>
   */
  boolean hasId();
  /**
   * <code>required string id = 1;</code>
   */
  java.lang.String getId();
  /**
   * <code>required string id = 1;</code>
   */
  com.google.protobuf.ByteString
      getIdBytes();

  /**
   * <code>required string username = 2;</code>
   */
  boolean hasUsername();
  /**
   * <code>required string username = 2;</code>
   */
  java.lang.String getUsername();
  /**
   * <code>required string username = 2;</code>
   */
  com.google.protobuf.ByteString
      getUsernameBytes();

  /**
   * <code>optional string password = 3;</code>
   */
  boolean hasPassword();
  /**
   * <code>optional string password = 3;</code>
   */
  java.lang.String getPassword();
  /**
   * <code>optional string password = 3;</code>
   */
  com.google.protobuf.ByteString
      getPasswordBytes();

  /**
   * <code>optional int32 age = 4;</code>
   */
  boolean hasAge();
  /**
   * <code>optional int32 age = 4;</code>
   */
  int getAge();

  /**
   * <code>optional .usersystem.UserModel.UserGender gender = 5;</code>
   */
  boolean hasGender();
  /**
   * <code>optional .usersystem.UserModel.UserGender gender = 5;</code>
   */
  com.wanghong.grpc.usersystem.proto.UserModel.UserGender getGender();

  /**
   * <code>optional string phone_number = 6;</code>
   */
  boolean hasPhoneNumber();
  /**
   * <code>optional string phone_number = 6;</code>
   */
  java.lang.String getPhoneNumber();
  /**
   * <code>optional string phone_number = 6;</code>
   */
  com.google.protobuf.ByteString
      getPhoneNumberBytes();

  /**
   * <code>optional .usersystem.Geo geo = 7;</code>
   */
  boolean hasGeo();
  /**
   * <code>optional .usersystem.Geo geo = 7;</code>
   */
  com.wanghong.grpc.usersystem.proto.Geo getGeo();

  /**
   * <code>optional uint64 create_at_millis = 8;</code>
   */
  boolean hasCreateAtMillis();
  /**
   * <code>optional uint64 create_at_millis = 8;</code>
   */
  long getCreateAtMillis();

  /**
   * <code>optional uint64 update_at_millis = 9;</code>
   */
  boolean hasUpdateAtMillis();
  /**
   * <code>optional uint64 update_at_millis = 9;</code>
   */
  long getUpdateAtMillis();
}
