#include <grpcpp/grpcpp.h>

#include <iostream>
#include <memory>
#include <string>

#include "protos/calculator.grpc.pb.h"

class CalculatorServiceImpl final : public Calculator::Service {
  grpc::Status Add(grpc::ServerContext*, const AddRequest* req,
                   AddResponse* res) override {
    res->set_c(req->a() + req->b());
    return grpc::Status::OK;
  }
};

int main(int argc, char** argv) {
  CalculatorServiceImpl service;

  grpc::ServerBuilder()
      .AddListeningPort("0.0.0.0:3000", grpc::InsecureServerCredentials())
      .RegisterService(&service)
      .BuildAndStart()
      ->Wait();

  return 0;
}
