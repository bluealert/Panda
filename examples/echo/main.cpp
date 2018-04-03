// curl -v -X POST -H "Content-Type: application/json" -d '{"username":"xyz","password":"xyz"}' http://127.0.0.1:8080/echo

#include <panda/Panda.h>
#include <iostream>

int main() {
  try {
    panda::Panda app(2);
    app.POST("/echo", [](panda::Context* c) {
      c->response().json(c->request().body());
    });
    app.run("127.0.0.1", "8080");
  } catch (const std::bad_alloc& e) {
    std::cerr << "Out of memory!" << std::endl;
  } catch (...) {
    std::cerr << "Internal error" << std::endl;
  }
  return 0;
}