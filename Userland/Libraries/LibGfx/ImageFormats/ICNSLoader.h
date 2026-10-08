#pragma once

#include <LibGfx/Forward.h>
#include <LibGfx/ImageFormats/ImageDecoder.h>

namespace Gfx {

class ICNSImageDecoderPlugin final : public ImageDecoderPlugin {
public:
    static bool sniff(ReadonlyBytes);
    static ErrorOr<NonnullOwnPtr<ImageDecoderPlugin>> create(ReadonlyBytes);

    explicit ICNSImageDecoderPlugin(ReadonlyBytes);
    virtual ~ICNSImageDecoderPlugin() override;

    virtual IntSize size() const override;
    virtual bool is_animated() const override;
    virtual size_t loop_count() const override;
    virtual size_t frame_count() const override;
    virtual ErrorOr<ImageFrame> frame(size_t index, int ideal_point_size = 0) const override;

private:
    ReadonlyBytes m_bytes;
    IntSize m_size { 256, 256 };
};

}