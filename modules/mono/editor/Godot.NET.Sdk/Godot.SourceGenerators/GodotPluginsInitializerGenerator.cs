using System.Text;
using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.Text;

namespace Godot.SourceGenerators
{
    [Generator]
    public class GodotPluginsInitializerGenerator : ISourceGenerator
    {
        public void Initialize(GeneratorInitializationContext context)
        {
        }

        public void Execute(GeneratorExecutionContext context)
        {
            if (context.IsGodotToolsProject())
                return;

            string source =
                @"using System;
using System.Runtime.InteropServices;
using Godot.Bridge;
using Godot.NativeInterop;

namespace GodotPlugins.Game
{
    internal static partial class Main
    {
        [UnmanagedCallersOnly(EntryPoint = ""godotsharp_game_main_init"")]
        private static godot_bool InitializeFromGameProject(IntPtr godotDllHandle, IntPtr outManagedCallbacks)
        {
            try
            {
                DllImportResolver dllImportResolver = new GodotDllImportResolver(godotDllHandle).OnResolveDllImport;

                var coreApiAssembly = typeof(Godot.Object).Assembly;

                NativeLibrary.SetDllImportResolver(coreApiAssembly, dllImportResolver);

                ManagedCallbacks.Create(outManagedCallbacks);

                ScriptManagerBridge.LookupScriptsInAssembly(typeof(GodotPlugins.Game.Main).Assembly);

                return godot_bool.True;
            }
            catch (Exception e)
            {
                Console.Error.WriteLine(e);
                return false.ToGodotBool();
            }
        }
    }
}
";

            context.AddSource("GodotPlugins.Game_Generated",
                SourceText.From(source, Encoding.UTF8));
        }
    }
}
