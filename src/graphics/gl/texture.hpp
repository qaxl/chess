#pragma once

#include <cstdint>
#include <string_view>

namespace ftd::gl
{
    enum class ActiveTextureSlot {
        Slot0 = 0x84C0,
        Slot1,
        Slot2,
        Slot3,
        Slot4,
        Slot5,
        Slot6,
        Slot7,
        Slot8,
        Slot9,
        Slot10,
        Slot11,
        Slot12,
        Slot13,
        Slot14,
        Slot15,
        Slot16,
        Slot17,
        Slot18,
        Slot19,
        Slot20,
        Slot21,
        Slot22,
        Slot23,
        Slot24,
        Slot25,
        Slot26,
        Slot27,
        Slot28,
        Slot29,
        Slot30,
        Slot31,
    };

    class Texture {
    public:
        Texture(std::string_view path);

        void bind(ActiveTextureSlot slot = ActiveTextureSlot::Slot0);

    private:
        uint32_t id_;
    };
}
