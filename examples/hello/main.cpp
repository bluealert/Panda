// curl -v http://127.0.0.1:8080/hello

#include <panda/Panda.h>
#include <iostream>

int main() {
  try {
    panda::Panda app(2);
    app.GET("/hello", [](panda::Context* c) {
      c->response().string("Hello Panda!");
    });
    app.run("127.0.0.1", "8080");
  } catch (const std::bad_alloc& e) {
    std::cerr << "Out of memory!" << std::endl;
  } catch (...) {
    std::cerr << "Internal error" << std::endl;
  }
  return 0;
}