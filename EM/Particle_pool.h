#ifndef _PARTICLE_POOL_H
#define _PARTICLE_POOL_H

using namespace Microsoft::WRL;
using namespace Windows::UI::Core;
using namespace DirectX;


#define MAX_PARTICLES 10000

#include"Particle.h"
#include"pch.h"

class Particle_pool
{
public:
  Particle_pool(void);
  void create(float, float, int);

  void update(float, float);
  void render(void);

  void initialize();
private:
  void remove(int);

  bool is_initialized;
  int active_particles_;
  Particle* head_;
  Particle particles[MAX_PARTICLES];

  ComPtr<ID3D11Device1>          dev_;        // Device interface.
  ComPtr<ID3D11DeviceContext1>   devcon_;     // Device context interface.

  ComPtr<IDXGISwapChain1>        swapchain_;  // Swap chain interface.
  ComPtr<ID3D11RenderTargetView> render_target_;
  ComPtr<ID3D11Buffer>           vertex_buffer_;

  ComPtr<ID3D11VertexShader>     vertex_shader_;
  ComPtr<ID3D11PixelShader>      pixel_shader_;
  ComPtr<ID3D11InputLayout>      input_layout_;
};

#endif