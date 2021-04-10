/*!
 * @file
 * @brief
 */

#include "tiny_uart_double.h"
#include "CppUTestExt/MockSupport.h"
#include "tiny_utils.h"

void send(i_tiny_uart_t* _self, uint8_t byte)
{
  reinterpret(self, _self, tiny_uart_double_t*);

  mock().actualCall("send").onObject(self).withParameter("byte", byte);

  if(self->auto_send_complete) {
    tiny_uart_double_trigger_send_complete(self);
  }
}

i_tiny_event_t* on_send_complete(i_tiny_uart_t* _self)
{
  reinterpret(self, _self, tiny_uart_double_t*);
  return &self->send_complete.interface;
}

i_tiny_event_t* on_receive(i_tiny_uart_t* _self)
{
  reinterpret(self, _self, tiny_uart_double_t*);
  return &self->receive.interface;
}

static const i_tiny_uart_api_t api = { send, on_send_complete, on_receive };

void tiny_uart_double_init(tiny_uart_double_t* self)
{
  self->interface.api = &api;
  self->auto_send_complete = false;
  tiny_event_init(&self->send_complete);
  tiny_event_init(&self->receive);
}

void tiny_uart_double_set_auto_send_complete(tiny_uart_double_t* self, bool enabled)
{
  self->auto_send_complete = enabled;
}

void tiny_uart_double_trigger_send_complete(tiny_uart_double_t* self)
{
  tiny_event_publish(&self->send_complete, nullptr);
}

void tiny_uart_double_trigger_receive(tiny_uart_double_t* self, uint8_t byte)
{
  tiny_uart_on_receive_args_t args = { byte };
  tiny_event_publish(&self->send_complete, &args);
}
