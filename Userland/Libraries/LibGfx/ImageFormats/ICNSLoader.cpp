#include <LibGfx/Bitmap.h>
#include <LibGfx/ImageFormats/ICNSLoader.h>

namespace Gfx {

bool ICNSImageDecoderPlugin::sniff(ReadonlyBytes bytes)
{
    if (bytes.size() < 8)
        return false;
    return bytes[0] == 'i' && bytes[1] == 'c' && bytes[2] == 'n' && bytes[3] == 's';
}

ErrorOr<NonnullOwnPtr<ImageDecoderPlugin>> ICNSImageDecoderPlugin::create(ReadonlyBytes bytes)
{
    if (!sniff(bytes))
        return Error::from_string_literal("ICNS: Cabecera inválida o archivo demasiado pequeño");

    return adopt_nonnull_own_ptr(*new ICNSImageDecoderPlugin(bytes));
}

ICNSImageDecoderPlugin::ICNSImageDecoderPlugin(ReadonlyBytes bytes)
    : m_bytes(bytes)
{
}

ICNSImageDecoderPlugin::~ICNSImageDecoderPlugin() = default;

IntSize ICNSImageDecoderPlugin::size() const
{
    return m_size;
}

bool ICNSImageDecoderPlugin::is_animated() const { return false; }
size_t ICNSImageDecoderPlugin::loop_count() const { return 0; }
size_t ICNSImageDecoderPlugin::frame_count() const { return 1; }

ErrorOr<ImageFrame> ICNSImageDecoderPlugin::frame(size_t, int) const
{
    auto bitmap = TRY(Bitmap::create(BitmapFormat::BGRA8888, m_size));
    return ImageFrame { .bitmap = move(bitmap), .duration = 0 };
}

}