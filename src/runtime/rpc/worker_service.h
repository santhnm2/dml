#ifndef RUNTIME_RPC_WORKER_SERVICE_H
#define RUNTIME_RPC_WORKER_SERVICE_H

#include <memory>
#include <iostream>
#include <queue>
#include <string>
#include <thread>

#include <grpc++/grpc++.h>

#include "../../graph/node.h"
#include "protos/node_def.pb.h"
#include "protos/worker_service.grpc.pb.h"

using grpc::Server;
using grpc::ServerAsyncResponseWriter;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerCompletionQueue;
using grpc::Status;
using dml::InitNodeRequest;
using dml::InitNodeResponse;
using dml::NodeDef;
using dml::Worker;

extern std::queue<Node*> fwd_waiting;
extern std::queue<Node*> fwd_ready;
extern std::queue<Node*> bwd;

class WorkerServiceImpl : public Worker::Service {
  Status InitNode(ServerContext* context, const InitNodeRequest* request,
                  InitNodeResponse* response) override {
    // TODO(santhnm2): for each NodeDef in request, add a Node* to fwd_waiting
    return Status::OK;
  }

  // TODO(santhnm2): add route for tensor transfer
};

#endif // RUNTIME_RPC_WORKER_SERVICE_H