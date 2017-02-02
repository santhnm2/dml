#ifndef RUNTIME_RPC_MASTER_CLIENT_H
#define RUNTIME_RPC_MASTER_CLIENT_H

#include <memory>
#include <string>
#include <vector>

#include <grpc++/grpc++.h>

#include "../../graph/node.h"
#include "protos/node_def.pb.h"
#include "protos//worker_service.grpc.pb.h"

using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::ClientContext;
using grpc::CompletionQueue;
using grpc::Status;
using dml::InitNodeRequest;
using dml::InitNodeResponse;
using dml::NodeDef;
using dml::Worker;

class MasterClient {
 public:
  MasterClient(std::shared_ptr<Channel> channel)
      : stub_(Worker::NewStub(channel)) {}

  std::string InitNode(std::vector<NodeDef> defs) {
    InitNodeRequest request;

    for (NodeDef def : defs) {
      NodeDef* def_empty = request.add_def();
      def_empty->CopyFrom(def);
    }

    InitNodeResponse response;

    ClientContext context;

    Status status = stub_->InitNode(&context, request, &response);

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