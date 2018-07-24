#include <radeon_rays.h>
#include <cassert>
#include <iostream>


using namespace RadeonRays;

int main(int argc, char* argv[]) {
  //choose device
  int nativeidx = -1;
  // Always use OpenCL
  IntersectionApi::SetPlatform(DeviceInfo::kOpenCL);
  
  for (auto idx = 0U; idx < IntersectionApi::GetDeviceCount(); ++idx)
    {
      DeviceInfo devinfo;
      IntersectionApi::GetDeviceInfo(idx, devinfo);
      
      if (devinfo.type == DeviceInfo::kGpu && nativeidx == -1)
	{
	  nativeidx = idx;
	}
    }
  assert(nativeidx != -1);
  IntersectionApi* api = IntersectionApi::Create(nativeidx);

  // Mesh vertices
  float vertices[] = {
    0.f,0.f,0.f,
    0.f,1.f,0.f,
    1.f,0.f,0.f
  };
  int indices[] = {0, 1, 2};
  // Number of vertices for the face
  int numfaceverts[] = { 3 };
  Shape* shape = api->CreateMesh(vertices, 3, 3*sizeof(float), indices, 0, numfaceverts, 1);
  shape->SetId(12345);
  std::cout << "The id of created shape " << shape->GetId() << "\n";
  api->AttachShape(shape);
  api->Commit();
  // Rays
  ray rays[3];
  // Prepare the ray
  rays[0].o = float4(0.f,0.f,-10.f, 1000.f);
  rays[0].d = float3(0.f,0.f,1.f);
  rays[1].o = float4(0.f,0.5f,-10.f, 1000.f);
  rays[1].d = float3(0.f,0.f,1.f);
  rays[2].o = float4(0.f,0.f,0.f, 0.f);
  rays[2].d = float3(0.f,0.f,0.f);
  // Intersection and hit data
  Intersection isect[3];
  auto isect_buffer = api->CreateBuffer(3 * sizeof(Intersection), nullptr);
  auto ray_buffer = api->CreateBuffer(3 * sizeof(ray), rays);
  
  // Intersect
  api->QueryIntersection(ray_buffer, 3, isect_buffer, nullptr, nullptr);

  //get results
  Event* e = nullptr;
  Intersection* tmp = nullptr;
  api->MapBuffer(isect_buffer, kMapRead, 0, 3 * sizeof(Intersection), (void**)&tmp, &e);
  //RadeonRays calls are asynchronous, so need to wait for calculation to complete.
  e->Wait();
  api->DeleteEvent(e);
  e = nullptr;

  isect[0] = tmp[0];
  isect[1] = tmp[1];
  isect[2] = tmp[2];

  std::cout << "First intersection " << isect[0].shapeid << "\n";
  std::cout << "Second intersection " << isect[1].shapeid << "\n";
  std::cout << "Third intersection " << isect[2].shapeid << "\n";    
}

