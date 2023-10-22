#include <grpcpp/grpcpp.h>

#include <iostream>
#include <memory>
#include <string>

#include "absl/strings/str_format.h"
#include "protos/calculator.grpc.pb.h"

int main(int argc, char** argv) {
  std::unique_ptr<Calculator::Stub> stub = Calculator::NewStub(
      grpc::CreateChannel("0.0.0.0:3000", grpc::InsecureChannelCredentials()));

  grpc::ClientContext ctx;
  AddRequest req;
  AddResponse res;

  req.set_a(1);
  req.set_b(2);

  grpc::Status status = stub->Add(&ctx, req, &res);

  if (status.ok()) {
    std::cout << "c: " << res.c() << std::endl;
  } else {
    std::cout << status.error_code() << ": " << status.error_message()
              << std::endl;
  }

  return 0;
}
