// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: usersystem.proto

package com.wanghong.grpc.usersystem.proto;

/**
 * Protobuf type {@code usersystem.CheckLoginResponse}
 */
public  final class CheckLoginResponse extends
    com.google.protobuf.GeneratedMessageLite<
        CheckLoginResponse, CheckLoginResponse.Builder> implements
    // @@protoc_insertion_point(message_implements:usersystem.CheckLoginResponse)
    CheckLoginResponseOrBuilder {
  private CheckLoginResponse() {
  }
  private int bitField0_;
  public static final int RESPONSE_FIELD_NUMBER = 1;
  private com.wanghong.grpc.usersystem.proto.CommonResponse response_;
  /**
   * <code>required .usersystem.CommonResponse response = 1;</code>
   */
  @java.lang.Override
  public boolean hasResponse() {
    return ((bitField0_ & 0x00000001) != 0);
  }
  /**
   * <code>required .usersystem.CommonResponse response = 1;</code>
   */
  @java.lang.Override
  public com.wanghong.grpc.usersystem.proto.CommonResponse getResponse() {
    return response_ == null ? com.wanghong.grpc.usersystem.proto.CommonResponse.getDefaultInstance() : response_;
  }
  /**
   * <code>required .usersystem.CommonResponse response = 1;</code>
   */
  private void setResponse(com.wanghong.grpc.usersystem.proto.CommonResponse value) {
    if (value == null) {
      throw new NullPointerException();
    }
    response_ = value;
    bitField0_ |= 0x00000001;
    }
  /**
   * <code>required .usersystem.CommonResponse response = 1;</code>
   */
  private void setResponse(
      com.wanghong.grpc.usersystem.proto.CommonResponse.Builder builderForValue) {
    response_ = builderForValue.build();
    bitField0_ |= 0x00000001;
  }
  /**
   * <code>required .usersystem.CommonResponse response = 1;</code>
   */
  @java.lang.SuppressWarnings({"ReferenceEquality"})
  private void mergeResponse(com.wanghong.grpc.usersystem.proto.CommonResponse value) {
    if (value == null) {
      throw new NullPointerException();
    }
    if (response_ != null &&
        response_ != com.wanghong.grpc.usersystem.proto.CommonResponse.getDefaultInstance()) {
      response_ =
        com.wanghong.grpc.usersystem.proto.CommonResponse.newBuilder(response_).mergeFrom(value).buildPartial();
    } else {
      response_ = value;
    }
    bitField0_ |= 0x00000001;
  }
  /**
   * <code>required .usersystem.CommonResponse response = 1;</code>
   */
  private void clearResponse() {  response_ = null;
    bitField0_ = (bitField0_ & ~0x00000001);
  }

  public static com.wanghong.grpc.usersystem.proto.CheckLoginResponse parseFrom(
      java.nio.ByteBuffer data)
      throws com.google.protobuf.InvalidProtocolBufferException {
    return com.google.protobuf.GeneratedMessageLite.parseFrom(
        DEFAULT_INSTANCE, data);
  }
  public static com.wanghong.grpc.usersystem.proto.CheckLoginResponse parseFrom(
      java.nio.ByteBuffer data,
      com.google.protobuf.ExtensionRegistryLite extensionRegistry)
      throws com.google.protobuf.InvalidProtocolBufferException {
    return com.google.protobuf.GeneratedMessageLite.parseFrom(
        DEFAULT_INSTANCE, data, extensionRegistry);
  }
  public static com.wanghong.grpc.usersystem.proto.CheckLoginResponse parseFrom(
      com.google.protobuf.ByteString data)
      throws com.google.protobuf.InvalidProtocolBufferException {
    return com.google.protobuf.GeneratedMessageLite.parseFrom(
        DEFAULT_INSTANCE, data);
  }
  public static com.wanghong.grpc.usersystem.proto.CheckLoginResponse parseFrom(
      com.google.protobuf.ByteString data,
      com.google.protobuf.ExtensionRegistryLite extensionRegistry)
      throws com.google.protobuf.InvalidProtocolBufferException {
    return com.google.protobuf.GeneratedMessageLite.parseFrom(
        DEFAULT_INSTANCE, data, extensionRegistry);
  }
  public static com.wanghong.grpc.usersystem.proto.CheckLoginResponse parseFrom(byte[] data)
      throws com.google.protobuf.InvalidProtocolBufferException {
    return com.google.protobuf.GeneratedMessageLite.parseFrom(
        DEFAULT_INSTANCE, data);
  }
  public static com.wanghong.grpc.usersystem.proto.CheckLoginResponse parseFrom(
      byte[] data,
      com.google.protobuf.ExtensionRegistryLite extensionRegistry)
      throws com.google.protobuf.InvalidProtocolBufferException {
    return com.google.protobuf.GeneratedMessageLite.parseFrom(
        DEFAULT_INSTANCE, data, extensionRegistry);
  }
  public static com.wanghong.grpc.usersystem.proto.CheckLoginResponse parseFrom(java.io.InputStream input)
      throws java.io.IOException {
    return com.google.protobuf.GeneratedMessageLite.parseFrom(
        DEFAULT_INSTANCE, input);
  }
  public static com.wanghong.grpc.usersystem.proto.CheckLoginResponse parseFrom(
      java.io.InputStream input,
      com.google.protobuf.ExtensionRegistryLite extensionRegistry)
      throws java.io.IOException {
    return com.google.protobuf.GeneratedMessageLite.parseFrom(
        DEFAULT_INSTANCE, input, extensionRegistry);
  }
  public static com.wanghong.grpc.usersystem.proto.CheckLoginResponse parseDelimitedFrom(java.io.InputStream input)
      throws java.io.IOException {
    return parseDelimitedFrom(DEFAULT_INSTANCE, input);
  }
  public static com.wanghong.grpc.usersystem.proto.CheckLoginResponse parseDelimitedFrom(
      java.io.InputStream input,
      com.google.protobuf.ExtensionRegistryLite extensionRegistry)
      throws java.io.IOException {
    return parseDelimitedFrom(DEFAULT_INSTANCE, input, extensionRegistry);
  }
  public static com.wanghong.grpc.usersystem.proto.CheckLoginResponse parseFrom(
      com.google.protobuf.CodedInputStream input)
      throws java.io.IOException {
    return com.google.protobuf.GeneratedMessageLite.parseFrom(
        DEFAULT_INSTANCE, input);
  }
  public static com.wanghong.grpc.usersystem.proto.CheckLoginResponse parseFrom(
      com.google.protobuf.CodedInputStream input,
      com.google.protobuf.ExtensionRegistryLite extensionRegistry)
      throws java.io.IOException {
    return com.google.protobuf.GeneratedMessageLite.parseFrom(
        DEFAULT_INSTANCE, input, extensionRegistry);
  }

  public static Builder newBuilder() {
    return (Builder) DEFAULT_INSTANCE.createBuilder();
  }
  public static Builder newBuilder(com.wanghong.grpc.usersystem.proto.CheckLoginResponse prototype) {
    return (Builder) DEFAULT_INSTANCE.createBuilder(prototype);
  }

  /**
   * Protobuf type {@code usersystem.CheckLoginResponse}
   */
  public static final class Builder extends
      com.google.protobuf.GeneratedMessageLite.Builder<
        com.wanghong.grpc.usersystem.proto.CheckLoginResponse, Builder> implements
      // @@protoc_insertion_point(builder_implements:usersystem.CheckLoginResponse)
      com.wanghong.grpc.usersystem.proto.CheckLoginResponseOrBuilder {
    // Construct using com.wanghong.grpc.usersystem.proto.CheckLoginResponse.newBuilder()
    private Builder() {
      super(DEFAULT_INSTANCE);
    }


    /**
     * <code>required .usersystem.CommonResponse response = 1;</code>
     */
    @java.lang.Override
    public boolean hasResponse() {
      return instance.hasResponse();
    }
    /**
     * <code>required .usersystem.CommonResponse response = 1;</code>
     */
    @java.lang.Override
    public com.wanghong.grpc.usersystem.proto.CommonResponse getResponse() {
      return instance.getResponse();
    }
    /**
     * <code>required .usersystem.CommonResponse response = 1;</code>
     */
    public Builder setResponse(com.wanghong.grpc.usersystem.proto.CommonResponse value) {
      copyOnWrite();
      instance.setResponse(value);
      return this;
      }
    /**
     * <code>required .usersystem.CommonResponse response = 1;</code>
     */
    public Builder setResponse(
        com.wanghong.grpc.usersystem.proto.CommonResponse.Builder builderForValue) {
      copyOnWrite();
      instance.setResponse(builderForValue);
      return this;
    }
    /**
     * <code>required .usersystem.CommonResponse response = 1;</code>
     */
    public Builder mergeResponse(com.wanghong.grpc.usersystem.proto.CommonResponse value) {
      copyOnWrite();
      instance.mergeResponse(value);
      return this;
    }
    /**
     * <code>required .usersystem.CommonResponse response = 1;</code>
     */
    public Builder clearResponse() {  copyOnWrite();
      instance.clearResponse();
      return this;
    }

    // @@protoc_insertion_point(builder_scope:usersystem.CheckLoginResponse)
  }
  private byte memoizedIsInitialized = 2;
  @java.lang.Override
  @java.lang.SuppressWarnings({"unchecked", "fallthrough"})
  protected final java.lang.Object dynamicMethod(
      com.google.protobuf.GeneratedMessageLite.MethodToInvoke method,
      java.lang.Object arg0, java.lang.Object arg1) {
    switch (method) {
      case NEW_MUTABLE_INSTANCE: {
        return new com.wanghong.grpc.usersystem.proto.CheckLoginResponse();
      }
      case NEW_BUILDER: {
        return new Builder();
      }
      case BUILD_MESSAGE_INFO: {
          java.lang.Object[] objects = new java.lang.Object[] {
            "bitField0_",
            "response_",
          };
          java.lang.String info =
              "\u0001\u0001\u0000\u0001\u0001\u0001\u0001\u0000\u0000\u0001\u0001\u0509\u0000";
          return newMessageInfo(DEFAULT_INSTANCE, info, objects);
      }
      // fall through
      case GET_DEFAULT_INSTANCE: {
        return DEFAULT_INSTANCE;
      }
      case GET_PARSER: {
        com.google.protobuf.Parser<com.wanghong.grpc.usersystem.proto.CheckLoginResponse> parser = PARSER;
        if (parser == null) {
          synchronized (com.wanghong.grpc.usersystem.proto.CheckLoginResponse.class) {
            parser = PARSER;
            if (parser == null) {
              parser = new DefaultInstanceBasedParser(DEFAULT_INSTANCE);
              PARSER = parser;
            }
          }
        }
        return parser;
    }
    case GET_MEMOIZED_IS_INITIALIZED: {
      return memoizedIsInitialized;
    }
    case SET_MEMOIZED_IS_INITIALIZED: {
      memoizedIsInitialized = (byte) (arg0 == null ? 0 : 1);
      return null;
    }
    }
    throw new UnsupportedOperationException();
  }


  // @@protoc_insertion_point(class_scope:usersystem.CheckLoginResponse)
  private static final com.wanghong.grpc.usersystem.proto.CheckLoginResponse DEFAULT_INSTANCE;
  static {
    // New instances are implicitly immutable so no need to make
    // immutable.
    DEFAULT_INSTANCE = new CheckLoginResponse();
  }

  static {
    com.google.protobuf.GeneratedMessageLite.registerDefaultInstance(
      CheckLoginResponse.class, DEFAULT_INSTANCE);
  }
  public static com.wanghong.grpc.usersystem.proto.CheckLoginResponse getDefaultInstance() {
    return DEFAULT_INSTANCE;
  }

  private static volatile com.google.protobuf.Parser<CheckLoginResponse> PARSER;

  public static com.google.protobuf.Parser<CheckLoginResponse> parser() {
    return DEFAULT_INSTANCE.getParserForType();
  }
}

