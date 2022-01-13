/*
 * Copyright (C) 2021 Huawei Device Co., Ltd.
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

#include "input_method_agent_proxy.h"

namespace OHOS {
namespace MiscServices {
    using namespace ErrorCode;
    InputMethodAgentProxy::InputMethodAgentProxy(const sptr<IRemoteObject> &object)
    : IRemoteProxy<IInputMethodAgent>(object)
    {
    }

    int32_t InputMethodAgentProxy::DispatchKey(int32_t key, int32_t status)
    {
        IMSA_HILOGI("InputMethodAgentProxy::DispatchKey key = %{public}d, status = %{public}d", key, status);
        MessageParcel data, reply;
        MessageOption option;
        if (!data.WriteInterfaceToken(GetDescriptor())) {
            IMSA_HILOGI("InputMethodAgentProxy::DispatchKey descriptor is not match");
            return ERROR_EX_PARCELABLE;
        }

        data.WriteInt32(key);
        data.WriteInt32(status);

        auto ret = Remote()->SendRequest(DISPATCH_KEY, data, reply, option);
        return ret;
    }

    void InputMethodAgentProxy::OnCursorUpdate(int32_t positionX, int32_t positionY, int32_t height)
    {
        IMSA_HILOGI("InputMethodAgentProxy::OnCursorUpdate");
        MessageParcel data, reply;
        MessageOption option;
        if (!data.WriteInterfaceToken(GetDescriptor())) {
            IMSA_HILOGI("InputMethodAgentProxy::OnCursorUpdate descriptor is not match");
            return;
        }

        data.WriteInt32(positionX);
        data.WriteInt32(positionY);
        data.WriteInt32(height);

        Remote()->SendRequest(ON_CURSOR_UPDATE, data, reply, option);
    }

    void InputMethodAgentProxy::OnSelectionChange(std::u16string text, int32_t oldBegin, int32_t oldEnd,
                                                  int32_t newBegin, int32_t newEnd)
    {
        IMSA_HILOGI("InputMethodAgentProxy::OnSelectionChange");
        MessageParcel data, reply;
        MessageOption option;
        if (!data.WriteInterfaceToken(GetDescriptor())) {
            IMSA_HILOGI("InputMethodAgentProxy::OnSelectionChange descriptor is not match");
            return;
        }

        data.WriteString16(text);
        data.WriteInt32(oldBegin);
        data.WriteInt32(oldEnd);
        data.WriteInt32(newBegin);
        data.WriteInt32(newEnd);

        Remote()->SendRequest(ON_SELECTION_CHANGE, data, reply, option);
    }
}
}
