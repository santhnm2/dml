#ifndef RUNTIME_RPC_WORKER_SERVICE_H
#define RUNTIME_RPC_WORKER_SERVICE_H

#include <memory>
#include <iostream>
#include <string>
#include <thread>
#include <unordered_set>

#include <grpc++/grpc++.h>
#include <pthread.h>

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

extern pthread_mutex_t waiting_lock;
extern pthread_cond_t waiting_cv;
extern std::unordered_set<Node*> fwd_waiting;
extern std::unordered_set<Node*> fwd_ready;
extern std::unordered_set<Node*> bwd;

class WorkerServiceImpl : public Worker::Service {
  Status InitNode(ServerContext* context, const InitNodeRequest* request,
                  InitNodeResponse* response) override {
    std::cout << "InitNode:entry" << std::endl; 
    pthread_mutex_lock(&waiting_lock);
    for (NodeDef def : request->def()) {
      Node* n = new Node(def);
     
      fwd_waiting.insert(n);

      // DEBUG
      // std::cout << "Added node " << n->name() << " to fwd_waiting."
      // << std::endl;
    }
    pthread_cond_signal(&waiting_cv);
    pthread_mutex_unlock(&waiting_lock);

    return Status::OK;
  }
};

#endif // RUNTIME_RPC_WORKER_SERVICE_H