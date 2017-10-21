%module gui

%include "../../math/swig/math.i"

%{
    #include "nyra/core/Path.h"
    #include "nyra/gui/Widget.h"
    #include "nyra/gui/Image.h"
%}

%include "std_string.i"
%include "nyra/gui/Widget.h"

%extend nyra::gui::Widget
{    
    void set_sprite(const std::string& filename)
    {
        const std::string pathname = nyra::core::path::join(
                nyra::core::DATA_PATH, "textures/" + filename);
        dynamic_cast<nyra::gui::Image*>($self)->initialize(pathname);
    }
}

%pythoncode
%{
Widget.visible = property(Widget.getVisible, Widget.setVisible)
%}
