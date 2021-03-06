// Generated by the smf_gen.
// Any local changes WILL BE LOST.
// source: ../src/rpc/smf_gen/demo_service
#pragma once
#ifndef SMF_DEMO_SERVICE__INCLUDED
#define SMF_DEMO_SERVICE__INCLUDED

#include "demo_service_generated.h"

#include <experimental/optional>
#include <rpc/rpc_service.h>
#include <rpc/rpc_client.h>
#include <rpc/rpc_recv_context.h>
#include <log.h>
namespace smf_gen {
namespace fbs {
namespace rpc {

class SmurfStorage: public smf::rpc_service {
 public:
  virtual const char *service_name() const override final {
    return "SmurfStorage";
  }
  virtual uint32_t service_id() const override final {
    return 1969906889;
  }
  virtual std::vector<smf::rpc_service_method_handle> methods() override final {
    using h = smf::rpc_service_method_handle;
    std::vector<h> handles;
    handles.emplace_back(
      "Get", 3312871568,
      [this](smf::rpc_recv_context c) -> future<smf::rpc_envelope> {
        return Get(std::move(c));
    });
    return handles;
  }
  virtual future<smf::rpc_envelope>
  Get(smf::rpc_recv_context rec) {
    /*Input type: Request*/
    /*Output type: Response*/
    smf::rpc_envelope e(nullptr);
    // Helpful for clients to set the status.
    // Typically follows HTTP style. Not imposed by smf whatsoever.
    e.set_status(200);
    return make_ready_future<smf::rpc_envelope>(std::move(e));
  }
}; // end of service: SmurfStorage

class SmurfStorageClient: public smf::rpc_client {
 public:
  SmurfStorageClient(ipv4_addr server_addr)
  :smf::rpc_client(std::move(server_addr)) {}

  future<smf::rpc_recv_ctx_t<Response>>
  GetSend(smf::rpc_envelope req) {
    // RequestID: 1969906889 ^ 3312871568
    // ServiceID: 1969906889 == crc32(ServiceName)
    // MethodID:  3312871568 == crc32(MethodName)
    req.set_request_id(1969906889, 3312871568);
    return send<Response>(req.to_temp_buf(),false);
  }
}; // end of rpc client: SmurfStorageClient

}  // namespace rpc
}  // namespace fbs
}  // namespace smf_gen


#endif  // SMF_DEMO_SERVICE__INCLUDED
