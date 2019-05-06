'use strict';

const glslDocPrefix = '<url>';
const glslDataStructuresUrl = `${glslDocPrefix}`;

const glslPrimitives = {
    // Scalars
    bool: 'Boolean',
    int: 'Integer',
    uint: 'Unsigned Integer',
    float: 'Number',
    double: 'Decimal',
    // Vectors
    bvec2: 'Boolean Vector2',
    bvec3: 'Boolean Vector3',
    bvec4: 'Boolean Vector4',
    ivec2: 'Integer Vector2',
    ivec3: 'Integer Vector3',
    ivec4: 'Integer Vector4',
    uvec2: 'Unsigned Integer Vector2',
    uvec3: 'Unsigned Integer Vectro3',
    uvec4: 'Unsigned Integer Vector4',
    vvec2: 'Float Vectro2',
    vvec3: 'Float Vector3',
    vvec4: 'Float Vector4',
    dvec2: 'Double Vector2',
    dvec3: 'Double Vector3',
    dvec4: 'Double Vector4',
    // Matrices
    // matn (n columns x n rows)
    mat2: 'Matrix 2x2',
    mat3: 'Matrix 3x3',
    mat4: 'Matrix 4x4',
    // matnxm (n columns x m rows)
    mat2x2: 'Matrix 2x2',
    mat2x3: 'Matrix 2x3',
    mat2x4: 'Matrix 2x4',
    mat3x2: 'Matrix 3x2',
    mat3x3: 'Matrix 3x3',
    mat3x4: 'Matrix 3x4',
    mat4x2: 'Matrix 4x2',
    mat4x3: 'Matrix 4x3',
    mat4x4: 'Matrix 4x4',
    // OpenGL Primitives -> URL: https://www.khronos.org/opengl/wiki/OpenGL_Type
    GLboolean: 'GLboolean',
    GLbyte: 'GLbyte',
    GLubyte: 'GLubyte',
    GLshort: 'GLshort',
    GLushort: 'GLushort',
    GLint: 'GLint',
    GLuint: 'GLuint',
    GLfixed: 'GLfixed',
    GLint64: 'GLint64',
    GLuint64: 'Gluint64',
    GLsizei: 'GLsizei',
    GLenum: 'Glenum',
    GLintptr: 'GLintptr',
    GLsizeiptr: 'GLsizeiptr',
    GLsync: 'GLsync',
    GLbitfield: 'GLbitfield',
    GLhalf: 'GLhalf',
    GLfloat: 'GLfloat',
    GLclampf: 'GLclampf',
    GLdouble: 'GLdouble',
    GLclampd: 'GLclampd'
};

const glGlobalObjectsUrl = `<url>`;
const glGlobalTypes = [];

const customTypesMap = {
    'Animation': 'Animation',
    'AnimationSP': 'Animation',
    'AnimationUP': 'Animation',
    'BumpMapCore': 'BumpMapCore',
    'BumpMapCoreSP': 'BumpMapCore',
    'BumpMapCoreUP': 'BumpMapCore',
    'Camera': 'Camera',
    'CameraSP': 'Camera',
    'CameraUP': 'Camera',
    'CameraController': 'CameraController',
    'CameraControllerSP': 'CameraController',
    'CameraControllerUP': 'CameraController',
    'Composite': 'Composite',
    'CompositeSP': 'Composite',
    'CompositeUP': 'Composite',
    'Controller': 'Controller',
    'ControllerSP': 'Controller',
    'ControllerUP': 'Controller',
    'ColorCore': 'ColorCore',
    'ColorCoreSP': 'ColorCore',
    'ColorCoreUP': 'ColorCore',
    'Core': 'Core',
    'CoreSP': 'Core',
    'CoreUP': 'Core',
    'CubeMapCore': 'CubeMapCore',
    'CubeMapCoreSP': 'CubeMapCore',
    'CubeMapCoreUP': 'CubeMapCore',
    'GeometryCore': 'GeometryCore',
    'GeometryCoreSP': 'GeometryCore',
    'GeometryCoreUP': 'GeometryCore',
    'GeometryCoreFactory': 'GeometryCoreFactory',
    'GeometryCoreFactorySP': 'GeometryCoreFactory',
    'GeometryCoreFactoryUP': 'GeometryCoreFactory',
    'Group': 'Group',
    'GroupSP': 'Group',
    'GroupUP': 'Group',
    'InfoTraverser': 'InfoTraverser',
    'InfoTraverserSP': 'InfoTraverser',
    'InfoTraverserUP': 'InfoTraverser',
    'KeyboardController': 'KeyboardController',
    'KeyboardControllerSP': 'KeyboardController',
    'KeyboardControllerUP': 'KeyboardController',
    'Leaf': 'Leaf',
    'LeafSP': 'Leaf',
    'LeafUP': 'Leaf',
    'Light': 'Light',
    'LightSP': 'Light',
    'LightUP': 'Light',
    'LightPosition': 'LightPosition',
    'LightPositionSP': 'LightPosition',
    'LightPositionUP': 'LightPosition',
    'MaterialCore': 'MaterialCore',
    'MaterialCoreSP': 'MaterialCore',
    'MaterialCoreUP': 'MaterialCore',
    'MouseController': 'MouseController',
    'MouseControllerSP': 'MouseController',
    'MouseControllerUP': 'MouseController',
    'Node': 'Node',
    'NodeSP': 'Node',
    'NodeUP': 'Node',
    'OrthographicCamera': 'OrthographicCamera',
    'OrthographicCameraSP': 'OrthographicCamera',
    'OrthographicCameraUP': 'OrthographicCamera',
    'PerspectiveCamera': 'PerspectiveCamera',
    'PerspectiveCameraSP': 'PerspectiveCamera',
    'PerspectiveCameraUP': 'PerspectiveCamera',
    'PreTraverser': 'PreTraverser',
    'PreTraverserSP': 'PreTraverser',
    'PreTraverserUP': 'PreTraverser',
    'Renderer': 'Renderer',
    'RendererSP': 'Renderer',
    'RendererUP': 'Renderer',
    'RenderState': 'RenderState',
    'RenderStateSP': 'RenderState',
    'RenderStateUP': 'RenderState',
    'RenderTraverser': 'RenderTraverser',
    'RenderTraverserSP': 'RenderTraverser',
    'RenderTraverserUP': 'RenderTraverser',
    'ShaderCore': 'ShaderCore',
    'ShaderCoreSP': 'ShaderCore',
    'ShaderCoreUP': 'ShaderCore',
    'ShaderCoreFactory': 'ShaderCoreFactory',
    'ShaderCoreFactorySP': 'ShaderCoreFactory',
    'ShaderCoreFactoryUP': 'ShaderCoreFactory',
    'Shape': 'Shape',
    'ShapeSP': 'Shape',
    'ShapeUP': 'Shape',
    'StandardRenderer': 'StandardRenderer',
    'StandardRendererSP': 'StandardRenderer',
    'StandardRendererUP': 'StandardRenderer',
    'TextureCore': 'TextureCore',
    'TextureCoreSP': 'TextureCore',
    'TextureCoreUP': 'TextureCore',
    'Texture2DCore': 'Texture2DCore',
    'Texture2DCoreSP': 'Texture2DCore',
    'Texture2DCoreUP': 'Texture2DCore',
    'TransformAnimation': 'TransformAnimation',
    'TransformAnimationSP': 'TransformAnimation',
    'TransformAnimationUP': 'TransformAnimation',
    'Transformation': 'Transformation',
    'TransformationSP': 'Transformation',
    'TransformationUP': 'Transformation',
    'Traverser': 'Traverser',
    'TraverserSP': 'Traverser',
    'TraverserUP': 'Traverser',
    'Viewer': 'Viewer',
    'ViewerSP': 'Viewer',
    'ViewerUP': 'Viewer',
    'ViewState': 'ViewState',
    'ViewStateSP': 'ViewState',
    'ViewStateUP': 'ViewState'
};

const arrayPart = /(?:\[])+$/; // Regular Expression for arrays
const ptrPart = /(?:\*)+$/; // Regular Expression for pointers
const refPart = /(?:\&)+$/; // Regular Expression for references

function toLink(typeInput) {
    const typeLinks = [];
    typeInput = typeInput.replace('{', '').replace('}', '');
    const typeTexts = typeInput.split('|');

    typeTexts.forEach((typeText) => {
        typeText = typeText.trim();
        if (typeText) {
            let typeUrl;

            // To support type[], type[][] etc., we store the full string
            // and use the bracket-less version to lookup the type URL.
            const typeTextFull = typeText;
            typeText = typeText.replace(arrayPart, '');
            // To support type*, type** etc., we store the full string
            // and use the star-less version to lookup the type URL.
            typeText = typeText.replace(ptrPart, '');
            // To support type&, type&& etc., we store the full string
            // and use the and-less version to lookup the type URL.
            typeText = typeText.replace(refPart, '');

            const primitive = glslPrimitives[typeText]; // Check if we have a glslPrimitive

            if (primitive !== undefined) {
                // We got a glslPrimitive, let's create the `typeUrl`
                typeUrl = `${glslDataStructuresUrl}#${primitive}_type`;
            } else if (glslGlobalTypes.includes(typeText)) {
                // Okay, it wasn`t a glslPrimitive but it was a global type
                typeUrl = `${glslGlobalObjectsUrl}${typeText}`;
            } else {
                // Nothing, let's try our custom types map
                typeUrl = customTypesMap[typeText];
            }

            if (typeUrl) { // Puhhh, we've found something (this should be the case)
                typeLinks.push(
                    `<a href="${typeUrl}" class="type">&lt;${typeTextFull}&gt;</a>`
                );
            } else { // Uh, we found nothing :( -> throw an Error
                throw new Error(
                    `Unrecognized type: '${typeTextFull}'.\n` +
                    "Please, edit the type or update the 'tools/doc/type-parser.js'."
                );
            }
        } else { // Wait, what?! There can't be a empty type slot!!!
            throw new Error(`Empty type slot: ${typeInput}`);
        }
    });

    return typeLinks.length ? typeLinks.join(' | ') : typeInput;
}

module.exports = { toLink };

