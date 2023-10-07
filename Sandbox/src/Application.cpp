namespace PIEngine {
	__declspec(dllimport) void print();
	//这里是导入
}

void main()
{
	PIEngine::print();
}