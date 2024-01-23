#include "Terrain.h"

Terrain::Terrain(float w, float h)
	: WIDTH(w), HEIGHT(h)
{
	// load height map texture
	const char* file = "Ressources/heightmaps/iceland_heightmap.png";
	int width, height, nChannels;
	data = stbi_load(file,
		&width, &height, &nChannels,
		0);

	if (!data) {
		std::cout << "Failed to load texture file " << file << std::endl;	
	}

	m_nChannels = nChannels;
	//WIDTH = width;
	//HEIGHT = height;
	//stbi_image_free(data);
			// retrieve texel for (i,j) tex coord
	unsigned char* texel = data + (12 + width * 5) * nChannels;
	// raw height at coordinate
	unsigned char y = texel[0];
	KGLOG(y)

	gridmesh = new VertexMesh[WIDTH*HEIGHT];
	m_indices = new uint32_t[(WIDTH - 1) * (HEIGHT - 1) * 6];

	gridmesh2 = new VertexMesh[WIDTH * HEIGHT];
	m_indices2 = new uint32_t[(WIDTH - 1) * (HEIGHT - 1) * 6];

	gridmesh = gridmesh2;
	m_indices = m_indices2;
	//std::cout << sizeof(gridmesh) << std::endl;

	GenerateTerrain();
	GenerateTerrain_v2();
	//- terrain
	m_VAOT = std::make_shared<VertexArray>();
	m_VAOT->Bind();
	m_VBOT = std::make_shared<VertexBuffer>(gridmesh2, sizeof(VertexMesh) * WIDTH * HEIGHT);
	BufferLayout layoutT = {
		{ShaderDataType::Float, "aAltitude"},
		{ShaderDataType::Float, "aAngle"},
	};
	m_VBOT->SetLayout(layoutT);

	m_IBOT = std::make_shared<IndexBuffer>(m_indices2, (WIDTH-1) * (HEIGHT-1) * 6);
	m_VAOT->AddVertexBuffer(m_VBOT);
	m_VAOT->SetIndexBuffer(m_IBOT);


	myshaderT = std::make_shared<Shader>("Ressources/shaders/terrainshader.vs", "Ressources/shaders/terrainshader.fs");
	myshaderT->use();

	//KGLOG(gridmesh[2].position.y)



}

Terrain::~Terrain()
{
}

void Terrain::GenerateTerrain()
{

	float Yheight;
	int i = 0;
	for (uint32_t x = 0; x < WIDTH; x++)
	{
		for (uint32_t z = 0; z < HEIGHT; z++)
		{

			Yheight = glm::gaussRand(0.2f, 0.5f);

			uint32_t j = (uint32_t)(z * (int)WIDTH + x);
			//gridmesh[j] = {
			//	glm::vec3((float)x - DX, Yheight , (float)z - DZ),
			//	glm::vec3(0.0f, glm::gaussRand(0.2f,0.09f), 0.0f) 
			//};
			gridmesh[j] = {
				Yheight , 0.0f
			};

			if (x < WIDTH - 1 && z < HEIGHT - 1)
			{
				m_indices[i]     = (z + 1) * WIDTH + (x);
				m_indices[i + 1] = (z) * WIDTH + (x);
				m_indices[i + 2] = (z) * WIDTH + (x + 1);
				m_indices[i + 3] = (z) * WIDTH + (x + 1);
				m_indices[i + 4] = (z + 1)*WIDTH + (x + 1);
				m_indices[i + 5] = (z + 1)*WIDTH + (x);
				i += 6;

			}

		}
	}
}

void Terrain::GenerateTerrain_v2()
{

	float Yheight;
	int i = 0;
	for (uint32_t x = 0; x < WIDTH; x++)
	{
		for (uint32_t z = 0; z < HEIGHT; z++)
		{

			Yheight = glm::gaussRand(-0.5f, -0.4f);

			uint32_t j = (uint32_t)(z * (int)WIDTH + x);
			//gridmesh2[j] = {
			//	glm::vec3((float)x, Yheight , (float)z),
			//	glm::vec3(0.0f, 0.0f, 0.0f)
			//};
			gridmesh2[j] = {
				Yheight ,0.0f
			};
			if (x < WIDTH - 1 && z < HEIGHT - 1)
			{
				m_indices2[i] = (z + 1) * WIDTH + (x);
				m_indices2[i + 1] = (z)*WIDTH + (x);
				m_indices2[i + 2] = (z)*WIDTH + (x + 1);
				m_indices2[i + 3] = (z)*WIDTH + (x + 1);
				m_indices2[i + 4] = (z + 1) * WIDTH + (x + 1);
				m_indices2[i + 5] = (z + 1) * WIDTH + (x);
				i += 6;

			}

		}
	}
}

void Terrain::GenerateIndex()
{

}

float Terrain::getheight(const float& x, const float& z)
{

	// retrieve texel for (i,j) tex coord
	int idx = (((int)x + (int)DX) + (int)WIDTH * ((int)z + (int)DZ)) * m_nChannels;
	if (idx < 0)
		KGLOG(idx)


	unsigned char* texel = data + idx;
	// raw height at coordinate
	unsigned char y = texel[0];

	float val = (float)y * yScale - yShift;

	return val;
}
float Terrain::getheight2(const float& x, const float& z)
{
	int idx = getindex(x, z);
	unsigned char* texel = data + idx;
	// raw height at coordinate
	unsigned char y = texel[0];
	float val1 = (float)y * yScale - yShift;

	idx = idx + 1;
	texel = data + idx;
	y = texel[0];
	float val2 = (float)y * yScale - yShift;

	idx = idx - 2;
	texel = data + idx;
	y = texel[0];
	float val3 = (float)y * yScale - yShift;

	idx = idx + 1 + WIDTH;
	texel = data + idx;
	y = texel[0];
	float val4 = (float)y * yScale - yShift;

	idx = idx - 2.0 * WIDTH;
	texel = data + idx;
	y = texel[0];
	float val5 = (float)y * yScale - yShift;

	return (val1 + val2 + val3 + val4 + val5) / 5.0f;
}
float Terrain::getheight_first(uint32_t x, uint32_t z)
{

	// retrieve texel for (i,j) tex coord
	unsigned char* texel = data + ((int)x + (int)WIDTH * (int)z) * m_nChannels;
	// raw height at coordinate
	unsigned char y = texel[0];

	return (float)y * yScale - yShift;
}

int Terrain::getindex(const float& x, const float& z)
{
	int idx = (((int)x + (int)DX) + (int)WIDTH * ((int)z + (int)DZ)) * m_nChannels;
	if (idx < 0)
		KGLOG(idx)

	return idx;
}