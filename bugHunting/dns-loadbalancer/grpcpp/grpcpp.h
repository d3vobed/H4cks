
GRPC C++  1.64.0
Main Page
Related Pages
Modules
Namespaces
Data Structures
Files

Search
include
grpc
grpc.h
Go to the documentation of this file.
 /*
  *
  * Copyright 2015-2016 gRPC authors.
  *
  * Licensed under the Apache License, Version 2.0 (the "License");
  * you may not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  *
  *     http://www.apache.org/licenses/LICENSE-2.0
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  */
  
 #ifndef GRPC_GRPC_H
 #define GRPC_GRPC_H
  
 #include <stddef.h>
  
 #include <grpc/byte_buffer.h>
 #include <grpc/impl/connectivity_state.h>  // IWYU pragma: export
 #include <grpc/impl/grpc_types.h>          // IWYU pragma: export
 #include <grpc/impl/propagation_bits.h>
 #include <grpc/slice.h>
 #include <grpc/status.h>
 #include <grpc/support/port_platform.h>
 #include <grpc/support/time.h>
  
 #ifdef __cplusplus
 extern "C" {
 #endif
  
 GRPCAPI void grpc_metadata_array_init(grpc_metadata_array* array);
 GRPCAPI void grpc_metadata_array_destroy(grpc_metadata_array* array);
  
 GRPCAPI void grpc_call_details_init(grpc_call_details* details);
 GRPCAPI void grpc_call_details_destroy(grpc_call_details* details);
  
 GRPCAPI void grpc_init(void);
  
 GRPCAPI void grpc_shutdown(void);
  
 GRPCAPI int grpc_is_initialized(void);
  
 GRPCAPI void grpc_shutdown_blocking(void);
  
 GRPCAPI const char* grpc_version_string(void);
  
 GRPCAPI const char* grpc_g_stands_for(void);
  
 GRPCAPI const grpc_completion_queue_factory*
 grpc_completion_queue_factory_lookup(
     const grpc_completion_queue_attributes* attributes);
  
 GRPCAPI grpc_completion_queue* grpc_completion_queue_create_for_next(
     void* reserved);
  
 GRPCAPI grpc_completion_queue* grpc_completion_queue_create_for_pluck(
     void* reserved);
  
 GRPCAPI grpc_completion_queue* grpc_completion_queue_create_for_callback(
     grpc_completion_queue_functor* shutdown_callback, void* reserved);
  
 GRPCAPI grpc_completion_queue* grpc_completion_queue_create(
     const grpc_completion_queue_factory* factory,
     const grpc_completion_queue_attributes* attributes, void* reserved);
  
 GRPCAPI grpc_event grpc_completion_queue_next(grpc_completion_queue* cq,
                                               gpr_timespec deadline,
                                               void* reserved);
  
 GRPCAPI grpc_event grpc_completion_queue_pluck(grpc_completion_queue* cq,
                                                void* tag, gpr_timespec deadline,
                                                void* reserved);
  
 #define GRPC_MAX_COMPLETION_QUEUE_PLUCKERS 6
  
 GRPCAPI void grpc_completion_queue_shutdown(grpc_completion_queue* cq);
  
 GRPCAPI void grpc_completion_queue_destroy(grpc_completion_queue* cq);
  
 /*********** EXPERIMENTAL API ************/
 GRPCAPI void grpc_completion_queue_thread_local_cache_init(
     grpc_completion_queue* cq);
  
 /*********** EXPERIMENTAL API ************/
 GRPCAPI int grpc_completion_queue_thread_local_cache_flush(
     grpc_completion_queue* cq, void** tag, int* ok);
  
 GRPCAPI grpc_connectivity_state grpc_channel_check_connectivity_state(
     grpc_channel* channel, int try_to_connect);
  
 GRPCAPI void grpc_channel_watch_connectivity_state(
     grpc_channel* channel, grpc_connectivity_state last_observed_state,
     gpr_timespec deadline, grpc_completion_queue* cq, void* tag);
  
 GRPCAPI int grpc_channel_support_connectivity_watcher(grpc_channel* channel);
  
 GRPCAPI grpc_call* grpc_channel_create_call(
     grpc_channel* channel, grpc_call* parent_call, uint32_t propagation_mask,
     grpc_completion_queue* completion_queue, grpc_slice method,
     const grpc_slice* host, gpr_timespec deadline, void* reserved);
  
 GRPCAPI void* grpc_channel_register_call(grpc_channel* channel,
                                          const char* method, const char* host,
                                          void* reserved);
  
 GRPCAPI grpc_call* grpc_channel_create_registered_call(
     grpc_channel* channel, grpc_call* parent_call, uint32_t propagation_mask,
     grpc_completion_queue* completion_queue, void* registered_call_handle,
     gpr_timespec deadline, void* reserved);
  
 GRPCAPI void* grpc_call_arena_alloc(grpc_call* call, size_t size);
  
 GRPCAPI grpc_call_error grpc_call_start_batch(grpc_call* call,
                                               const grpc_op* ops, size_t nops,
                                               void* tag, void* reserved);
  
 GRPCAPI char* grpc_call_get_peer(grpc_call* call);
  
 struct census_context;
  
 GRPCAPI void grpc_census_call_set_context(grpc_call* call,
                                           struct census_context* context);
  
 GRPCAPI struct census_context* grpc_census_call_get_context(grpc_call* call);
  
 GRPCAPI char* grpc_channel_get_target(grpc_channel* channel);
  
 GRPCAPI void grpc_channel_get_info(grpc_channel* channel,
                                    const grpc_channel_info* channel_info);
  
 GRPCAPI void grpc_channel_reset_connect_backoff(grpc_channel* channel);
  
 typedef struct grpc_channel_credentials grpc_channel_credentials;
  
 GRPCAPI void grpc_channel_credentials_release(grpc_channel_credentials* creds);
  
 typedef struct grpc_server_credentials grpc_server_credentials;
  
 GRPCAPI void grpc_server_credentials_release(grpc_server_credentials* creds);
  
 GRPCAPI grpc_channel* grpc_channel_create(const char* target,
                                           grpc_channel_credentials* creds,
                                           const grpc_channel_args* args);
  
 GRPCAPI grpc_channel* grpc_lame_client_channel_create(
     const char* target, grpc_status_code error_code, const char* error_message);
  
 GRPCAPI void grpc_channel_destroy(grpc_channel* channel);
  
 GRPCAPI grpc_call_error grpc_call_cancel(grpc_call* call, void* reserved);
  
 GRPCAPI grpc_call_error grpc_call_cancel_with_status(grpc_call* call,
                                                      grpc_status_code status,
                                                      const char* description,
                                                      void* reserved);
  
 /* Returns whether or not the call's receive message operation failed because of
  * an error (as opposed to a graceful end-of-stream) */
 GRPCAPI int grpc_call_failed_before_recv_message(const grpc_call* c);
  
 GRPCAPI void grpc_call_ref(grpc_call* call);
  
 GRPCAPI void grpc_call_unref(grpc_call* call);
  
 typedef struct grpc_call_credentials grpc_call_credentials;
  
 GRPCAPI grpc_call_error grpc_call_set_credentials(grpc_call* call,
                                                   grpc_call_credentials* creds);
  
 GRPCAPI grpc_call_error grpc_server_request_call(
     grpc_server* server, grpc_call** call, grpc_call_details* details,
     grpc_metadata_array* request_metadata,
     grpc_completion_queue* cq_bound_to_call,
     grpc_completion_queue* cq_for_notification, void* tag_new);
  
 typedef enum {
   GRPC_SRM_PAYLOAD_NONE,
   GRPC_SRM_PAYLOAD_READ_INITIAL_BYTE_BUFFER
 } grpc_server_register_method_payload_handling;
  
 GRPCAPI void* grpc_server_register_method(
     grpc_server* server, const char* method, const char* host,
     grpc_server_register_method_payload_handling payload_handling,
     uint32_t flags);
  
 GRPCAPI grpc_call_error grpc_server_request_registered_call(
     grpc_server* server, void* registered_method, grpc_call** call,
     gpr_timespec* deadline, grpc_metadata_array* request_metadata,
     grpc_byte_buffer** optional_payload,
     grpc_completion_queue* cq_bound_to_call,
     grpc_completion_queue* cq_for_notification, void* tag_new);
  
 GRPCAPI grpc_server* grpc_server_create(const grpc_channel_args* args,
                                         void* reserved);
  
 GRPCAPI void grpc_server_register_completion_queue(grpc_server* server,
                                                    grpc_completion_queue* cq,
                                                    void* reserved);
  
 // More members might be added in later, so users should take care to memset
 // this to 0 before using it.
 typedef struct {
   grpc_status_code code;
   const char* error_message;
 } grpc_serving_status_update;
  
 // There might be more methods added later, so users should take care to memset
 // this to 0 before using it.
 typedef struct {
   void (*on_serving_status_update)(void* user_data, const char* uri,
                                    grpc_serving_status_update update);
   void* user_data;
 } grpc_server_xds_status_notifier;
  
 typedef struct grpc_server_config_fetcher grpc_server_config_fetcher;
  
 GRPCAPI grpc_server_config_fetcher* grpc_server_config_fetcher_xds_create(
     grpc_server_xds_status_notifier notifier, const grpc_channel_args* args);
  
 GRPCAPI void grpc_server_config_fetcher_destroy(
     grpc_server_config_fetcher* config_fetcher);
  
 GRPCAPI void grpc_server_set_config_fetcher(
     grpc_server* server, grpc_server_config_fetcher* config_fetcher);
  
 GRPCAPI int grpc_server_add_http2_port(grpc_server* server, const char* addr,
                                        grpc_server_credentials* creds);
  
 GRPCAPI void grpc_server_start(grpc_server* server);
  
 GRPCAPI void grpc_server_shutdown_and_notify(grpc_server* server,
                                              grpc_completion_queue* cq,
                                              void* tag);
  
 GRPCAPI void grpc_server_cancel_all_calls(grpc_server* server);
  
 GRPCAPI void grpc_server_destroy(grpc_server* server);
  
 GRPCAPI int grpc_tracer_set_enabled(const char* name, int enabled);
  
 GRPCAPI int grpc_header_key_is_legal(grpc_slice slice);
  
 GRPCAPI int grpc_header_nonbin_value_is_legal(grpc_slice slice);
  
 GRPCAPI int grpc_is_binary_header(grpc_slice slice);
  
 GRPCAPI const char* grpc_call_error_to_string(grpc_call_error error);
  
 GRPCAPI grpc_resource_quota* grpc_resource_quota_create(const char* trace_name);
  
 GRPCAPI void grpc_resource_quota_ref(grpc_resource_quota* resource_quota);
  
 GRPCAPI void grpc_resource_quota_unref(grpc_resource_quota* resource_quota);
  
 GRPCAPI void grpc_resource_quota_resize(grpc_resource_quota* resource_quota,
                                         size_t new_size);
  
 GRPCAPI void grpc_resource_quota_set_max_threads(
     grpc_resource_quota* resource_quota, int new_max_threads);
  
 GRPCAPI grpc_slice grpc_dump_xds_configs(void);
  
 GRPCAPI const grpc_arg_pointer_vtable* grpc_resource_quota_arg_vtable(void);
  
 /************* CHANNELZ API *************/
 /* Gets all root channels (i.e. channels the application has directly
    created). This does not include subchannels nor non-top level channels.
    The returned string is allocated and must be freed by the application. */
 GRPCAPI char* grpc_channelz_get_top_channels(intptr_t start_channel_id);
  
 /* Gets all servers that exist in the process. */
 GRPCAPI char* grpc_channelz_get_servers(intptr_t start_server_id);
  
 /* Returns a single Server, or else a NOT_FOUND code. */
 GRPCAPI char* grpc_channelz_get_server(intptr_t server_id);
  
 /* Gets all server sockets that exist in the server. */
 GRPCAPI char* grpc_channelz_get_server_sockets(intptr_t server_id,
                                                intptr_t start_socket_id,
                                                intptr_t max_results);
  
 /* Returns a single Channel, or else a NOT_FOUND code. The returned string
    is allocated and must be freed by the application. */
 GRPCAPI char* grpc_channelz_get_channel(intptr_t channel_id);
  
 /* Returns a single Subchannel, or else a NOT_FOUND code. The returned string
    is allocated and must be freed by the application. */
 GRPCAPI char* grpc_channelz_get_subchannel(intptr_t subchannel_id);
  
 /* Returns a single Socket, or else a NOT_FOUND code. The returned string
    is allocated and must be freed by the application. */
 GRPCAPI char* grpc_channelz_get_socket(intptr_t socket_id);
  
 GRPCAPI const grpc_arg_pointer_vtable*
 grpc_authorization_policy_provider_arg_vtable(void);
  
 #ifdef __cplusplus
 }
 #endif
  
 #endif /* GRPC_GRPC_H */
Generated on Fri May 17 2024 01:17:15 for GRPC C++ by   doxygen 1.8.17s
