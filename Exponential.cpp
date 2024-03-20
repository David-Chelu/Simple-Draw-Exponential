#include "Code/TGL/TGL.h"



namespace Exponent
{
    largeuint_t
        exponent{2};
}



largeuint_t f(largeuint_t x)
{
    return TGL::Pow(x, Exponent::exponent);
}



int main()
{
    const COLORREF
        color{TGL::Pixel(0, 127, 0)};

    constexpr largeuint_t
        factor = 2500,
        width  = 1280,
        height = 720;



    StartTGL();



    TGL::tglWindow
        window;

    TGL::tglVideo
        video;

    TGL::tglBitmap
        result;



    window.planned.style  = WS_BORDER;
    window.planned.width  = width;
    window.planned.height = height;
    window.Center();

    window.Create();
    window.Show();

    video = window;
    video.SetMode(TGL::VideoMode::Bitmap);
    video = result;

    result.planned.width  = window.current.width;
    result.planned.height = window.current.height;

    result.Allocate();

    for (largeuint_t x = 0; x < result.current.width; ++x)
    {
        for (largeuint_t y = 0; y < TGL::Min(f(x) / factor, result.current.height); ++y)
        {
            result(result.current.height - y - 1)[x] = color;
        }
    }



    video.Lock();

    video.Display();

    video.Unlock();

    LoopStart
    {
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            break;
        }
    }
    LoopEnd



    EndTGL();
}
