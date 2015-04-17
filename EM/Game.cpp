#include"pch.h"
#include"Game.h"

#include<fstream>
using std::ifstream;
using std::string;

Array<byte>^ load_shader_file(string file)
{
  Array<byte>^ file_data = nullptr;

  // Open the file
  ifstream vertex_file(file, std::ios::in | std::ios::binary | std::ios::ate);

  if (vertex_file.is_open()) // Open was successful
  {
    int length = (int)vertex_file.tellg();

    // Collect file data
    file_data = ref new Array<byte>(length);
    vertex_file.seekg(0, std::ios::beg);
    vertex_file.read(reinterpret_cast<char*>(file_data->Data), length);
    vertex_file.close();
  }

  return file_data;
}

// Initializes and prepares D3D
void CGame::initialize(void)
{
  // Define temp ptrs.
  ComPtr<ID3D11Device>        dev11;
  ComPtr<ID3D11DeviceContext> devcon11;

  // Create device and context.
  D3D11CreateDevice(
    nullptr,
    D3D_DRIVER_TYPE_HARDWARE,
    nullptr,
    0,
    nullptr,
    0,
    D3D11_SDK_VERSION,
    &dev11,
    nullptr,
    &devcon11);

  // Convert pointers from DX11 versions to the DX11.1 versions
  dev11.As(&dev_);
  devcon11.As(&devcon_);

  // Obtain DXGI factory.
  ComPtr<IDXGIDevice1> dxgi_device;
  dev_.As(&dxgi_device);
  //// Get access to the adapter.
  ComPtr<IDXGIAdapter> dxgi_adapter;
  dxgi_device->GetAdapter(&dxgi_adapter);
  //// Get access to the factor.
  ComPtr<IDXGIFactory2> dxgi_factory;
  dxgi_adapter->GetParent(__uuidof(IDXGIFactory2), &dxgi_factory);

  // Setup swap chain description
  DXGI_SWAP_CHAIN_DESC1 scd = { 0 };
  scd.BufferUsage      = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  scd.BufferCount      = 2;
  scd.Format           = DXGI_FORMAT_B8G8R8A8_UNORM;
  scd.SwapEffect       = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
  scd.SampleDesc.Count = 1;

  CoreWindow^ window = CoreWindow::GetForCurrentThread(); // Get window pointer.

  dxgi_factory->CreateSwapChainForCoreWindow(
    dev_.Get(),
    reinterpret_cast<IUnknown*>(window),
    &scd,
    nullptr,
    &swapchain_);

  // Get a pointer to the back buffer.
  ComPtr<ID3D11Texture2D> backbuffer;
  swapchain_->GetBuffer(0, __uuidof(ID3D11Texture2D), &backbuffer);
  // Create render target.
  dev_->CreateRenderTargetView(backbuffer.Get(), nullptr, &render_target_);

  // Set the viewport.
  D3D11_VIEWPORT viewport = { 0 };
  viewport.TopLeftX = 0;
  viewport.TopLeftY = 0;
  viewport.Width = window->Bounds.Width;
  viewport.Height = window->Bounds.Height;

  devcon_->RSSetViewports(1, &viewport);

  init_graphics();
  init_pipeline();
}

void CGame::init_graphics(void)
{
  Vertex vertices[] =
  {
    {  0.0f,   0.5f, 0.0f },
    {  0.45f, -0.5f, 0.0f },
    { -0.45f, -0.5f, 0.0f },
  };

  D3D11_BUFFER_DESC bd = { 0 };
  bd.ByteWidth = sizeof(Vertex) * ARRAYSIZE(vertices);
  bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

  D3D11_SUBRESOURCE_DATA srd = { vertices, 0, 0 };

  dev_->CreateBuffer(&bd, &srd, &vertex_buffer_);
}

void CGame::init_pipeline(void)
{
  // Load shader files.
  Array<byte>^ vs_file = load_shader_file("VertexShader.cso");
  Array<byte>^ ps_file = load_shader_file("PixelShader.cso");

  // Create shader objects.
  dev_->CreateVertexShader(vs_file->Data, vs_file->Length, nullptr, &vertex_shader_);
  dev_->CreatePixelShader(ps_file->Data, ps_file->Length, nullptr, &pixel_shader_);

  // Set as active shaders.
  devcon_->VSSetShader(vertex_shader_.Get(), nullptr, 0);
  devcon_->PSSetShader(pixel_shader_.Get(), nullptr, 0);

  // Initialize input layout.
  D3D11_INPUT_ELEMENT_DESC ied[] = 
  {
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
  };

  // Create input layout.
  dev_->CreateInputLayout(ied, ARRAYSIZE(ied), vs_file->Data, vs_file->Length, &input_layout_);
  devcon_->IASetInputLayout(input_layout_.Get());

  particles.initialize();
}

// Performs state updates
void CGame::update(void)
{
}

// Renders a single frame
void CGame::render(void)
{
  // Set new render target.
  devcon_->OMSetRenderTargets(1, render_target_.GetAddressOf(), nullptr);

  // Clear back buffer.
  float color[4] = { 0.0f, 0.2f, 0.4f, 1.0f };
  devcon_->ClearRenderTargetView(render_target_.Get(), color);

  // Set the vertex buffer.
  UINT stride = sizeof(Vertex);
  UINT offset = 0;
  devcon_->IASetVertexBuffers(0, 1, vertex_buffer_.GetAddressOf(), &stride, &offset);

  // Set primitive topology.
  devcon_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

  // Draw vertices starting from 0.
  devcon_->Draw(3, 0);

  // Swap the buffers.
  swapchain_->Present(1, 0);
}

void CGame::particle_burst(float x_origin, float y_origin, int qty)
{
  particles.create(x_origin, y_origin, qty);
}