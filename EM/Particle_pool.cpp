#include"pch.h"
#include"Particle_pool.h"

#include<cstdlib>

using std::rand;

Particle_pool::Particle_pool(void) : is_initialized(false), active_particles_(0)
{
  head_ = particles;
  for (unsigned i = 1; i < MAX_PARTICLES; ++i)
  {
    particles[i].set_next(particles + (i - 1));
  }
  particles[MAX_PARTICLES - 1].set_next(NULL);
}

void Particle_pool::create(float init_x, float init_y, int qty)
{
  Random velocity(-1.0f, 1.0f);
  Random color(0.0f, 1.0f);
  Random mass(1.0f, 100.0f);

  for (int i = 0; i < qty && head_; ++i)
  {
    Particle p;

    float x_velocity = velocity();
    float y_velocity = velocity();

    int m = (int)mass();

    float colors[4] = { color(), color(), color(), 1.0f };

    Particle* tmp = head_;
    head_ = head_->get_next();

    tmp->init(
      init_x,
      init_y,
      x_velocity,
      y_velocity,
      m,
      colors
      );

    ++active_particles_;
  }
}

void Particle_pool::update(float mouse_x, float mouse_y)
{
  int count = 0; // Exit loop early if all active particles have been drawn
  int deactivated = 0;
  for (unsigned i = 0; i < MAX_PARTICLES && count < active_particles_; ++i)
  {
    if (particles[i].is_active())
    {
      count++;
      if (particles[i].animate(0, 0))
      {
        ++deactivated;
        remove(i);
      }
    }
  }

  active_particles_ -= deactivated;
}

void Particle_pool::remove(int index)
{
  if (active_particles_ == 0)
    return;

  particles[index].set_next(head_);
  head_ = particles + index;
  --active_particles_;
}

void Particle_pool::initialize()
{
  if (is_initialized)
    return;



  D3D11_INPUT_ELEMENT_DESC ied[] =
  {
    { "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 8, D3D11_INPUT_PER_VERTEX_DATA, 0 },
  };
  
  is_initialized = true;
}
