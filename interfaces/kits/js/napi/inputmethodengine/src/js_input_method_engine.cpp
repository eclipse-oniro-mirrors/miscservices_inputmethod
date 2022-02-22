/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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
 */
#include "js_input_method_engine.h"
#include "input_method_controller.h"
#include "napi/native_api.h"
#include "napi/native_node_api.h"
#include "event_handler.h"
#include "event_runner.h"
#include "string_ex.h"
#include "js_input_method_engine_listener.h"
#include "input_method_ability.h"
#include "global.h"
namespace OHOS {
namespace MiscServices {
    constexpr size_t ARGC_TWO = 2;
    JsInputMethodEngine::JsInputMethodEngine(NativeEngine* engine)
    {
        IMSA_HILOGI("JsInputMethodEngine::Constructor is called");
        imeListener_ = new JsInputMethodEngineListener(engine);
        InputMethodAbility::GetInstance()->setImeListener(imeListener_);
    }

    void JsInputMethodEngine::Finalizer(NativeEngine* engine, void* data, void* hint)
    {
        IMSA_HILOGI("JsInputMethodEngine::Finalizer is called");
        std::unique_ptr<JsInputMethodEngine>(static_cast<JsInputMethodEngine*>(data));
    }

    NativeValue* JsInputMethodEngine::RegisterCallback(NativeEngine* engine, NativeCallbackInfo* info)
    {
        JsInputMethodEngine* me = AbilityRuntime::CheckParamsAndGetThis<JsInputMethodEngine>(engine, info);
        return (me != nullptr) ? me->OnRegisterCallback(*engine, *info) : nullptr;
    }

    NativeValue* JsInputMethodEngine::UnRegisterCallback(NativeEngine* engine, NativeCallbackInfo* info)
    {
        JsInputMethodEngine* me = AbilityRuntime::CheckParamsAndGetThis<JsInputMethodEngine>(engine, info);
        return (me != nullptr) ? me->OnUnRegisterCallback(*engine, *info) : nullptr;
    }

    NativeValue* JsInputMethodEngine::OnRegisterCallback(NativeEngine& engine, NativeCallbackInfo& info)
    {
        IMSA_HILOGI("JsInputMethodEngine::OnRegisterCallback is called!");
        if (info.argc != ARGC_TWO) {
            IMSA_HILOGI("JsInputMethodEngine::OnRegisterCallback Params not match");
            return engine.CreateUndefined();
        }

        std::string cbType;
        if (!AbilityRuntime::ConvertFromJsValue(engine, info.argv[0], cbType)) {
            IMSA_HILOGI("JsInputMethodEngine::OnRegisterCallback Failed to convert parameter to callbackType");
            return engine.CreateUndefined();
        }

        NativeValue* value = info.argv[1];
        imeListener_->RegisterListenerWithType(engine, cbType, value);
        return engine.CreateUndefined();
    }

    NativeValue* JsInputMethodEngine::OnUnRegisterCallback(NativeEngine& engine, NativeCallbackInfo& info)
    {
        IMSA_HILOGI("JsInputMethodEngine::OnUnRegisterCallback is called!");
        if (info.argc == 0) {
            IMSA_HILOGI("JsInputMethodEngine::OnUnRegisterCallback Params not match");
            return engine.CreateUndefined();
        }

        std::string cbType;
        if (!AbilityRuntime::ConvertFromJsValue(engine, info.argv[0], cbType)) {
            IMSA_HILOGI("JsInputMethodEngine::OnUnRegisterCallback Failed to convert parameter to callbackType");
            return engine.CreateUndefined();
        }

        std::lock_guard<std::mutex> lock(mtx_);
        NativeValue* value = info.argv[1];
        if (!value->IsCallable()) {
            IMSA_HILOGI("JsInputMethodEngine::OnUnregisterWindowManagerCallback info->argv[1] is not callable");
            return engine.CreateUndefined();
        }
        imeListener_->UnregisterListenerWithType(cbType, value);
        return engine.CreateUndefined();
    }
}
}