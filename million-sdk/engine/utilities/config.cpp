#include "config.hpp"
#include <fstream>
#include <shlobj.h>
#pragma comment(lib, "shell32.lib")
#include <direct.h>

void get_config_path(char* buf, char* file_name)
{
	char my_documents[MAX_PATH];
	HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents);

	strcat(my_documents, "\\millionware");
	_mkdir(my_documents);

	strcat(my_documents, "\\");
	strcat(my_documents, file_name);

	strcpy(buf, my_documents);
}

void __forceinline load_file(const char* file_name, std::vector<char>* buf)
{
	std::ifstream file_stream(file_name, std::ios::binary);
	buf->assign(std::istreambuf_iterator<char>(file_stream), std::istreambuf_iterator<char>());
	file_stream.close();
}

namespace config
{
	void load_from_file(const char* file_name)
	{
		char file_path[512] = { 0 };
		get_config_path(file_path, (char*)file_name);

		std::vector<char> data;
		load_file(file_path, &data);

		load(data);
	}

	void save_to_file(const char* file_name)
	{
		char file_path[512] = { 0 };
		get_config_path(file_path, (char*)file_name);

		auto data = dump();

		std::ofstream fout(file_path, std::ios::out | std::ios::binary);
		fout.write(data.data(), data.size());
		fout.close();
	}
}