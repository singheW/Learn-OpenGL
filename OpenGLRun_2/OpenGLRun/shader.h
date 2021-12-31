#pragma once

//编写、编译、管理着色器是件麻烦事。最后，我们写一个类来让我们的生活轻松一点，
//它可以从硬盘读取着色器，然后编译并链接它们，并对它们进行错误检测，
//这就变得很好用了。这也会让你了解该如何封装目前所学的知识到一个抽象对象中。
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // 包含glad来获取所有的必须OpenGL头文件

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader
{
public:
    // 程序ID
    unsigned int ID;


    //使用C++文件流读取着色器内容，储存到几个string对象里：
         // 构造器读取并构建着色器
    Shader(const char* vertexPath, const char* fragmentPath)
    {
        // 1. 从文件路径中获取顶点/片段着色器
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // 保证ifstream对象可以抛出异常：
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // 打开文件
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // 读取文件的缓冲内容到数据流中
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // 关闭文件处理器
            vShaderFile.close();
            fShaderFile.close();
            // 转换数据流到string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        //下一步，我们需要编译和链接着色器。注意，我们也将检查编译 / 链接是否失败，
        //如果失败则打印编译时错误，调试的时候这些错误输出会及其重要
        //（你总会需要这些错误日志的）：
        // 2. 编译着色器
        unsigned int vertex, fragment;
        //  int success;
         // char infoLog[512];

          // 顶点着色器
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
        // 打印编译错误（如果有的话）
       // glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
       // if (!success)
       // {
      //      glGetShaderInfoLog(vertex, 512, NULL, infoLog);
      //      std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
       // };

        // 片段着色器也类似
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");

        // 着色器程序
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");
        // 打印连接错误（如果有的话）
       // glGetProgramiv(ID, GL_LINK_STATUS, &success);
        //if (!success)
      //  {
      //      glGetProgramInfoLog(ID, 512, NULL, infoLog);
      //      std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
      //  }

        // 删除着色器，它们已经链接到我们的程序中了，已经不再需要了
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }
    // 使用/激活程序
    void use()
    {
        glUseProgram(ID);
    }
    //  uniform工具函数
    void setBool(const std::string& name, bool value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }
    void setInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    void setFloat(const std::string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }

    //使用这个着色器类很简单；只要创建一个着色器对象，从那一点开始我们就可以开始使用了：
    //Shader ourShader("path/to/shaders/shader.vs", "path/to/shaders/shader.fs");
    //...
    //while (...)
    //{
      //  ourShader.use();
        //ourShader.setFloat("someUniform", 1.0f);
        //DrawStuff();
    //}





private:
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(unsigned int shader, std::string type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
};
#endif
