#include <node.h>
#include "Core/matrix.h"

namespace eigen {

using v8::Local;
using v8::Object;

void InitAll(Local<Object> exports) {
    Matrix::Init(exports);
}

NODE_MODULE(eigen, InitAll)

}
