#pragma once
class Component;
class ButtonListener {
public:
	virtual void actionPerformed(Component *) = 0;
};
