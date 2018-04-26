#ifndef CALLER_H
#define CALLER_H


// GLEW lib: needs to be included first!!
#include <GL/glew.h>

// OpenGL library
#include <GL/gl.h>

// OpenGL Utility library
#include <GL/glu.h>

#include <string>


namespace gl
{
    /**
     * @brief Error thrown when an OpenGL operation fails.
     */
    class opengl_error
    {
    public:
        /**
         * @brief Initializes a new instance of the opengl_error class.
         *
         * @param  error    OpenGL error code
         * @param  extraMsg Extra information to include in what()
         */
        explicit opengl_error(GLenum error, const std::string &extraMsg);
    };

    /**
     * @brief Throws an opengl_error if glGetError returns non-zero
     *
     * @throws opengl_error
     */
    void check_errors();

    /**
     * @brief Invokes the given OpenGL function
     *
     * @param  function OpenGL function to invoke
     *
     * @throws opengl_error
     */
    template<typename glFunction>
    auto gl_call(glFunction function)->typename
                    std::enable_if<std::is_same<void, decltype(function())>::value,
                    decltype(function())>::type
    {
        function();
        check_errors();
    }

    /**
     * @brief Invokes the given OpenGL function
     *
     * @param  function OpenGL function to invoke
     * @return          Return value of the OpenGL function
     *
     * @throws opengl_error
     */
    template<typename glFunction>
    auto gl_call(glFunction function)->typename
                    std::enable_if<!std::is_same<void, decltype(function())>::value,
                    decltype(function())>::type
    {
        auto ret = function();
        check_errors();

        return ret;
    }

    /**
     * @brief Invokes the given OpenGL function
     *
     * @param  function OpenGL function to invoke
     * @param  params   Parameters to forward to the OpenGL function
     *
     * @throws opengl_error
     */
    template<typename glFunction, typename... Params>
    auto gl_call(glFunction function, Params... params)->typename
                    std::enable_if<std::is_same<void, decltype(function(params...))>::value,
                    decltype(function(params...))>::type
    {
        function(std::forward<Params>(params)...);
        check_errors();
    }

    /**
     * @brief Invokes the given OpenGL function
     *
     * @param  function OpenGL function to invoke
     * @param  params   Parameters to forward to the OpenGL function
     * @return          Return value of the OpenGL function
     *
     * @throws opengl_error
     */
    template<typename glFunction, typename... Params>
    auto gl_call(glFunction function, Params... params)->typename
                    std::enable_if<!std::is_same<void, decltype(function(params...))>::value,
                    decltype(function(params...))>::type
    {
        auto ret = function(std::forward<Params>(params)...);
        check_errors();
        return ret;

    }
}



#endif // CALLER_H
