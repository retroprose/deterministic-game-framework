using System.ComponentModel;
using System.Diagnostics.CodeAnalysis;
using System.Diagnostics.Tracing;
using System.Globalization;
using System.Text.Json;
using System.Text.Json.Nodes;

namespace gen;


public class PrefabGenerator
{
    public static PrefabGenerator Create(string prefabPath, string outPath)
    {
        return new PrefabGenerator {
            OutPath = outPath,
            PrefabPath = prefabPath
        };
    }

    public PrefabGenerator() {
        OutPath = "";
        PrefabPath = "";
    }

    public string OutPath;
    public string PrefabPath;

    public class Def {
        public Def(string[] list, string def, string pre = "")
        {
            Prefix = pre;
            DefaultValue = def;
            List = list;
        }
        public string DefaultValue;
        public string Prefix;
        public string[] List;
    }

    public List<Def> Definitions = [
        // type component
        new Def(["Type"], "Null", "ObjType::"),
        
        // body component
        new Def(["Body", "position", "x"], "0"),
        new Def(["Body", "position", "y"], "0"),
        new Def(["Body", "velocity", "x"], "0"),
        new Def(["Body", "velocity", "y"], "0"),
        new Def(["Body", "size", "x"], "0"),
        new Def(["Body", "size", "y"], "0"),

        // player component
        new Def(["Player", "slot"], "0"),
        new Def(["Player", "delayFire"], "0"),
        new Def(["Player", "damage"], "0"),

        // enemy component
        new Def(["Enemy", "counter"], "0"),
        new Def(["Enemy", "delayFire"], "0"),
        new Def(["Enemy", "direction"], "0"),

        // animator component
        new Def(["Animator", "frame"], "_null", "AniFrame::"),
        new Def(["Animator", "count"], "0")
    ];

    public void Generate()
    {
        JsonNode? root = JsonValue.Parse(File.ReadAllText(PrefabPath));
        if (root == null)
        {
            return;
        }

        var sw  = new StringWriter();

        sw.WriteLine("/*");

        var sep = "";

        foreach (var node in root.AsArray())
        {
            var the_type = "__TYPE_ERROR__";
            if (node != null)
            {
                var tmp = node.AsObject()["Type"];
                if (tmp != null)
                {
                    the_type = tmp.ToString();
                } 
            }

            sw.Write(sep);
            sw.WriteLine($"    // {the_type}");
            foreach (var def in Definitions)
            {   
                var value = def.DefaultValue;
                JsonNode? iter = node;
                var index = 0;
                while (iter != null && index < def.List.Length)
                {
                    JsonObject? objNode = null;
                    if (iter != null)
                    {
                        objNode = iter.AsObject();
                    }
                    if (objNode != null && objNode.ContainsKey(def.List[index]))
                    {
                        iter = objNode[def.List[index]];
                    }
                    else
                    {
                        iter = null;
                    }
                    index++;
                }
                if (iter != null)
                {
                    //value = def.Prefix + iter.ToJsonString();
                    value = def.Prefix + iter.ToString();
                }

                var variable = "r";
                for (int i = 0; i < def.List.Length; i++)
                {
                    variable += $".{def.List[i].ToLower()}";    
                }

                sw.WriteLine($"    {variable} = {value};");

            }

            sep = "\n";

        }

    sw.WriteLine("*/");


      #region UglyTextPrefabs
        File.WriteAllText($"{OutPath}prefabs.hpp", @$"{sw.ToString()}");
        #endregion

    }



}



/*


#ifndef GENERATED_PREFABS_HPP
#define GENERATED_PREFABS_HPP


#include <everything.hpp>

struct Prefabs {

    static void create() {

    }


};

#endif // GENERATED_PREFABS_HPP


*/