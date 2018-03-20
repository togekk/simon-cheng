#include <emscripten/emscripten.h>
#include <emscripten/val.h>
#include <rapidjson/document.h>
#include <string>

using namespace std;
using namespace emscripten;
using namespace rapidjson;

extern "C" {
val layer = val::object();
val first = val::object();
// string opacity;
int frame;
int item_id;
int item_count = 100;

val render_node(val parent, string type, Value &attr, int text)
{
    val layer_return = val::object();
    if (!type.empty())
    {
        val layer_new = val::global("document").call<val>("createElement", type);
        if (!attr.ObjectEmpty())
        {
            for (Value::ConstMemberIterator M = attr.MemberBegin(); M != attr.MemberEnd(); M++)
            {
                string key = M->name.GetString();
                string value = M->value.GetString();
                layer_new.call<val>("setAttribute", key, value);
            }
        }
        // if (!text.empty())
        // {
        val text_new = val::global("document").call<val>("createTextNode", text);
        layer_new.call<val>("appendChild", text_new);
        // }
        parent.call<val>("appendChild", layer_new);
        layer_return = layer_new;
    }
    else
    {
        layer_return = parent;
    }
    return layer_return;
}

void get_item(int i)
{
    string id_str = "fuck";
    id_str.append(to_string(i));
    first = val::global("document").call<val>("getElementById", id_str);
}

void render()
{
    float opacity = (float)frame / 10;
    first["style"].set("opacity", opacity);
    frame++;
    if (frame > 10)
    {
        if (item_id < item_count - 1)
        {
            frame = 0;
            item_id++;
            get_item(item_id);
        }
        else
        {
            emscripten_cancel_main_loop();
        }
    }
}

void animate()
{
    Document attr;
    attr.SetObject();

    Value style;
    style = "opacity: 0";
    attr.AddMember("style", style, attr.GetAllocator());
    layer = val::global("document").call<val>("createDocumentFragment");
    for (int i = 0; i < item_count; i++)
    {
        string id_str = "fuck";
        id_str.append(to_string(i));
        Value id;
        id.SetString(id_str.c_str(), id_str.length());
        attr.AddMember("id", id, attr.GetAllocator());
        render_node(layer, "div", (Value &)attr, i);
    }
    val::global("document")["body"].call<val>("appendChild", layer);

    string id_str = "fuck";
    id_str.append(to_string(0));
    first = val::global("document").call<val>("getElementById", id_str);
    get_item(item_id);
    emscripten_set_main_loop(render, 60, 1);
}

int main()
{
    animate();
    return 0;
}
}
