#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ciParamsApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void ciParamsApp::setup()
{
}

void ciParamsApp::mouseDown( MouseEvent event )
{
}

void ciParamsApp::update()
{
}

void ciParamsApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( ciParamsApp, RendererGl )
