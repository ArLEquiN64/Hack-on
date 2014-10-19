#pragma once
class window {
public:
	window(int x, int y, int sizeX, int sizeY);
	~window();

	void drawWindow();
	void setWindow();
	void setString(char str[8][256],int low);
	void setString();

private:
	int handle;
	int back;
	int x, y;
	int sizeX, sizeY;
};