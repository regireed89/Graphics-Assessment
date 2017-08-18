#pragma once
struct GLFWwindow;
class Application
{
public:
	Application();
	virtual ~Application();
	void run(const char* title, unsigned width, unsigned height, bool fullscreen);
protected:
	virtual void startup() = 0;
	virtual void shutdown() = 0;
	virtual void update(float) = 0;
	virtual void draw() = 0;
	GLFWwindow* m_window;
	bool m_gameover;
};

