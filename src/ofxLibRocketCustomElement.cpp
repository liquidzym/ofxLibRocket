#include "ofxLibRocketCustomElement.h"

using namespace Rocket::Core;

ofxLibRocketCustomElementWrapper::ofxLibRocketCustomElementWrapper(string tagName, ofxLibRocketCustomElement* el):Element(tagName.c_str())
{	
	customElement = el;
}

void ofxLibRocketCustomElementWrapper::OnUpdate()
{
	customElement->update();
}

void ofxLibRocketCustomElementWrapper::OnRender()
{
	customElement->draw();
}

/******************************************************************************************************************************************************************************/

map<string, ofxLibRocketCustomElementInstancer*> ofxLibRocketCustomElementHandler::instancers;
ofxLibRocketCustomElementHandler* ofxLibRocketCustomElementHandler::singleton = NULL;

ofxLibRocketCustomElementHandler::ofxLibRocketCustomElementHandler()
{
}

ofxLibRocketCustomElementHandler::~ofxLibRocketCustomElementHandler()
{
}

Rocket::Core::Element* ofxLibRocketCustomElementHandler::InstanceElement(Rocket::Core::Element* parent, const Rocket::Core::String& tag, const Rocket::Core::XMLAttributes& attributes)
{
	if(instancers.find(tag.CString()) != instancers.end()){
		ofxLibRocketCustomElement* el = instancers[tag.CString()]->createInstance();
		Rocket::Core::Element* elRet = el->createRocketElement(tag.CString());
		el->setRootElement(new ofxLibRocketElement(elRet));
		el->setup();
		return elRet;
	}
	return NULL; //shouldn't happen	
}

void ofxLibRocketCustomElementHandler::Release()
{
}

void ofxLibRocketCustomElementHandler::ReleaseElement(Rocket::Core::Element* element)
{
	
}

ofxLibRocketCustomElementHandler* ofxLibRocketCustomElementHandler::get()
{
	if(singleton == NULL)
		singleton = new ofxLibRocketCustomElementHandler();
	return singleton;
}

/*********************************************************************************/

ofxLibRocketCustomElement::ofxLibRocketCustomElement()
{
	isSetup = false;
}

ofxLibRocketCustomElement::~ofxLibRocketCustomElement()
{

}

void ofxLibRocketCustomElement::ProcessEvent(Rocket::Core::Event& e)
{
	
}

void ofxLibRocketCustomElement::OnUpdate()
{
	if(!isSetup){
		setup();
		isSetup = true;
	}
}

Rocket::Core::Element* ofxLibRocketCustomElement::createRocketElement(string tagName)
{
	return new ofxLibRocketCustomElementWrapper(tagName, this);
}


void ofxLibRocketCustomElement::setRootElement(ofxLibRocketElement* el){
	rootElement = el;
}