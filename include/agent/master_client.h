#ifndef RUNTIME_RPC_MASTER_CLIENT_H
#define RUNTIME_RPC_MASTER_CLIENT_H

#include <memory>
#include <string>
#include <vector>

#include <grpc++/grpc++.h>

#include "agent/node.h"
#include "node_def.pb.h"
#include "worker_service_grpc.grpc.pb.h"

using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::ClientContext;
using grpc::CompletionQueue;
using grpc::Status;
using dml::InitRequest;
using dml::InitResponse;
using dml::NodeDef;
using dml::Worker;

class MasterClient {
 public:
  MasterClient(std::shared_ptr<Channel> channel)
      : stub_(Worker::NewStub(channel)) {}

  std::string Init(std::vector<NodeDef> defs, int iterations) {
    InitRequest request;

    for (NodeDef def : defs) {
      NodeDef* def_empty = request.add_def();
      def_empty->CopyFrom(def);
    }

    request.set_iterations(iterations);

    InitResponse response;

    ClientContext context;

    Status status = stub_->Init(&context, request, &response);

    if (status.ok()) {
      // TODO(santhnm2): define behavior on success
      return response.message();
    } else {
      // TODO(santhnm2): define behavior on failure
      return status.error_message();
    }
  }

 private:
  std::unique_ptr<Worker::Stub> stub_;
};

#endif // RUNTIME_RPC_MASTER_CLIENT_H