#pragma once

//��д�����롢������ɫ���Ǽ��鷳�¡��������дһ�����������ǵ���������һ�㣬
//�����Դ�Ӳ�̶�ȡ��ɫ����Ȼ����벢�������ǣ��������ǽ��д����⣬
//��ͱ�úܺ����ˡ���Ҳ�������˽����η�װĿǰ��ѧ��֪ʶ��һ����������С�
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // ����glad����ȡ���еı���OpenGLͷ�ļ�

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader
{
public:
    // ����ID
    unsigned int ID;


    //ʹ��C++�ļ�����ȡ��ɫ�����ݣ����浽����string�����
         // ��������ȡ��������ɫ��
    Shader(const char* vertexPath, const char* fragmentPath)
    {
        // 1. ���ļ�·���л�ȡ����/Ƭ����ɫ��
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ��֤ifstream��������׳��쳣��
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // ���ļ�
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // ��ȡ�ļ��Ļ������ݵ���������
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // �ر��ļ�������
            vShaderFile.close();
            fShaderFile.close();
            // ת����������string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        //��һ����������Ҫ�����������ɫ����ע�⣬����Ҳ�������� / �����Ƿ�ʧ�ܣ�
        //���ʧ�����ӡ����ʱ���󣬵��Ե�ʱ����Щ��������ἰ����Ҫ
        //�����ܻ���Ҫ��Щ������־�ģ���
        // 2. ������ɫ��
        unsigned int vertex, fragment;
        //  int success;
         // char infoLog[512];

          // ������ɫ��
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
        // ��ӡ�����������еĻ���
       // glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
       // if (!success)
       // {
      //      glGetShaderInfoLog(vertex, 512, NULL, infoLog);
      //      std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
       // };

        // Ƭ����ɫ��Ҳ����
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");

        // ��ɫ������
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");
        // ��ӡ���Ӵ�������еĻ���
       // glGetProgramiv(ID, GL_LINK_STATUS, &success);
        //if (!success)
      //  {
      //      glGetProgramInfoLog(ID, 512, NULL, infoLog);
      //      std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
      //  }

        // ɾ����ɫ���������Ѿ����ӵ����ǵĳ������ˣ��Ѿ�������Ҫ��
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }
    // ʹ��/�������
    void use()
    {
        glUseProgram(ID);
    }
    //  uniform���ߺ���
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

    //ʹ�������ɫ����ܼ򵥣�ֻҪ����һ����ɫ�����󣬴���һ�㿪ʼ���ǾͿ��Կ�ʼʹ���ˣ�
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
