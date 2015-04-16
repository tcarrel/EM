#ifndef _GAME_H
#define _GAME_H

using namespace Microsoft::WRL;
using namespace Windows::UI::Core;
using namespace DirectX;

#include"Vertex.h"

class CGame
{
public:
  ComPtr<ID3D11Device1>          dev_;        // Device interface.
  ComPtr<ID3D11DeviceContext1>   devcon_;     // Device context interface.
  
  ComPtr<IDXGISwapChain1>        swapchain_;  // Swap chain interface.
  ComPtr<ID3D11RenderTargetView> render_target_;
  ComPtr<ID3D11Buffer>           vertex_buffer_;
  
  ComPtr<ID3D11VertexShader>     vertex_shader_;
  ComPtr<ID3D11PixelShader>      pixel_shader_;
  ComPtr<ID3D11InputLayout>      input_layout_;

  void initialize(void);
  void init_graphics(void);
  void init_pipeline(void);

  void update(void);
  void render(void);
};

#endif