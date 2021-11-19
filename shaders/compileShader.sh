
ShaderDir=$(cd $(dirname ${BASH_SOURCE[0]}); pwd )
ShaderSource=$ShaderDir/frag.frag
ShaderTarget=$ShaderDir/frag.spv
if [ -f "$ShaderTarget" ]; then
    rm $ShaderTarget
fi
    glslc -c $ShaderSource -o $ShaderTarget

ShaderSource=$ShaderDir/vert.vert
ShaderTarget=$ShaderDir/vert.spv
if [ -f "$ShaderTarget" ]; then
    rm $ShaderTarget
fi
    glslc -c $ShaderSource -o $ShaderTarget
