def _impl(repository_ctx):
  # only run in macOS
  if repository_ctx.which("brew") == None:
    return

  # ["grpc", "openssl", "protobuf"]
  for lib in ["openssl"]:
    result = repository_ctx.execute(["brew", "--prefix", lib])
    result_path = result.stdout.splitlines()[0]
    repository_ctx.symlink(result_path, lib)

  repository_ctx.file("BUILD", """
package(default_visibility = ["//visibility:public"])
cc_library(
  name = "brew_library",
  #srcs = ["grpc/lib/libgrpc++.dylib", "openssl/lib/libssl.dylib", "openssl/lib/libcrypto.dylib", "protobuf/lib/libprotobuf.dylib"],
  #hdrs = glob(["grpc/include/**", "openssl/include/**", "protobuf/include/**", "protobuf/include/**"]),
  #includes = ["grpc/include", "protobuf/include", "openssl/include"],
  srcs = ["openssl/lib/libssl.dylib", "openssl/lib/libcrypto.dylib"],
  hdrs = glob(["openssl/include/**"]),
  #with includes, binary don't need to add copts -Ixxx
  includes = ["openssl/include"],
  visibility = ["//visibility:public"],
)
""")

brew_configure = repository_rule(
	  implementation=_impl,
	  local = True,
	  environ = [])
