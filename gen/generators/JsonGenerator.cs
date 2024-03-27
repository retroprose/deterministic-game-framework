using System.Diagnostics.CodeAnalysis;
using System.Diagnostics.Tracing;
using System.Globalization;
using System.Text.Json;
using System.Text.Json.Nodes;

namespace gen;


public class JsonGenerator
{
    public static JsonGenerator Create(string jsonPath, string outPath)
    {
        return new JsonGenerator {
            OutPath = outPath,
            JsonPath = jsonPath
        };
    }

    public JsonGenerator() {
        OutPath = "";
        JsonPath = "";
    }

    public string OutPath; 
    public string JsonPath;
    
    public void Generate()
    {
        var list = Directory.GetFiles(JsonPath);
        var root = new JsonObject();
        foreach (var file in list)
        {
            var name = GetName(file);
            var json = JsonNode.Parse(File.ReadAllText(file));
            root.Add(KeyValuePair.Create<string, JsonNode?>(name, json));
        }

        var sw = new StringWriter();       
        PrintNode(sw, root, 2);
        
        #region UglyTextJsons
        File.WriteAllText($"{OutPath}jsons.hpp", @$"#ifndef GENERATED_JSONS_HPP
#define GENERATED_JSONS_HPP

#include <cassert>

#include <json/json.hpp>


struct Jsons {{

    using k = JsonKeyValue;

    inline static const JsonValue& get(const char* s) {{        
        static JsonValue r = {sw.ToString()};
        return r[s];
    }}
}};

#endif // GENERATED_JSONS_HPP");
        #endregion
    
    }

    public string GetName(string s)
    {
        var sep = '\\';
        if (s.Contains("/"))
        {
            sep = '/';
        }
        var split = s.Split(sep);
        var temp = split[split.Length - 1];
        var split2 = temp.Split('.');
        var end = split2[0];
        return end;
    }

    public string MakeTabs(int number)
    {
        var s = "";
        for (int i = 0; i < number; i++)
        {
            //s += "\t"
            //s += "  ";
            s += "    ";
        }
        return s;
    }

    public void PrintNode(StringWriter sw, JsonNode? node, int depth = 0)
    {
        if (node == null)
        {
            sw.Write("nullptr");
        }
        else if (node.GetType() == typeof(System.Text.Json.Nodes.JsonObject))
        {
            var sep = "";
            var tabsOuter = MakeTabs(depth);
            var tabsInner = MakeTabs(depth + 1);
            sw.Write($"{{\n");
            foreach (var pair in node.AsObject())
            {
                sw.Write($"{sep}{tabsInner}k(\"{pair.Key}\", ");
                PrintNode(sw, pair.Value, depth + 1);
                sw.Write($")");
                sep = ",\n";
            }
            sw.Write($"\n{tabsOuter}}}");
        }
        else if (node.GetType() == typeof(System.Text.Json.Nodes.JsonArray))
        {
            var sep = "";
            var tabsOuter = MakeTabs(depth);
            var tabsInner = MakeTabs(depth + 1);
            sw.Write($"{{\n");
            foreach (var child in node.AsArray())
            {
                sw.Write($"{sep}{tabsInner}");
                PrintNode(sw, child, depth + 1);
                sw.Write("");
                sep = ",\n";
            }
            sw.Write($"\n{tabsOuter}}}");
        }
        else
        {
            // print the leaf!
            sw.Write(node.ToJsonString().Trim());
        }
    }

    

}
