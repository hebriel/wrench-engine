//
// @authors {underdisk}
// License : LGPLv3
//

#pragma once

#include <initializer_list>
#include <string>
#include <list>
#include "../gl/gl.h" //todo: remove that guy maybe

namespace wrench {

	/**
	* @brief Represent a Rendering Type
	*/
	enum class DataType : uint8_t
	{
		Float,
		Vec2,
		Vec3,
		Vec4,
		Mat3,
		Mat4,
		Int,
		Vec2i,
		Vec3i,
		Vec4i,
		Bool
	};

	/**
	* @brief Get the dimension of a DataType (1 for float, 2 for Vec2, 3 for Vec3...)
	*
	* This function is constexpr, try to use it with compile-time constant data if you need to
	*
	* @return 32 bits unsigned int representing the dimension of the DataType
	*/
	constexpr uint32_t data_type_dimension(const DataType& dataType)
	{
		switch(dataType)
		{
			case DataType::Float :	return 1;
			case DataType::Vec2 :	return 2;
			case DataType::Vec3 :	return 3;
			case DataType::Vec4 :	return 4;

			case DataType::Mat3 :	return 3 * 3;
			case DataType::Mat4 :	return 4 * 4;

			case DataType::Int :	return 1;
			case DataType::Vec2i :	return 2;
			case DataType::Vec3i :	return 3;
			case DataType::Vec4i :	return 4;

			case DataType::Bool :	return 1;
		}
	}

	/**
	* @brief Get the size of a DataType in bytes
	*
	* This function is constexpr, try to use it with compile-time constant data if you need to
	*
	* @return 32 bits unsigned int representing the size of the DataType in bytes
	*/
	constexpr uint32_t data_type_size(const DataType& dataType)
	{
		switch(dataType)
		{
			case DataType::Float	:
			case DataType::Vec2		:
			case DataType::Vec3		:
			case DataType::Vec4		:
			case DataType::Mat3		:
			case DataType::Mat4		:
				return data_type_dimension(dataType) * sizeof(float);

			case DataType::Int		:
			case DataType::Vec2i	:
			case DataType::Vec3i	:
			case DataType::Vec4i	:
				return data_type_dimension(dataType) * sizeof(uint32_t);

			case DataType::Bool		:
				return data_type_dimension(dataType) * sizeof(bool);
		}
	}

	/**
	* @brief Get the OpenGL enum type of a DataType
	*
	* This function is constexpr, try to use it with compile-time constant data if you need to
	*
	* @return 32 bits unsigned int (synonym to GLenum) representing the OpenGL enum type of the DataType (GL_FLOAT, GL_BOOL...)
	*/
	constexpr uint32_t data_type_gl_type(const DataType& dataType)
	{
		switch(dataType)
		{
			case DataType::Float	:
			case DataType::Vec2		:
			case DataType::Vec3		:
			case DataType::Vec4		:
			case DataType::Mat3		:
			case DataType::Mat4		:
				return GL_FLOAT;

			case DataType::Int		:
			case DataType::Vec2i	:
			case DataType::Vec3i	:
			case DataType::Vec4i	:
				return GL_INT;

			case DataType::Bool		:
				return GL_BOOL;
		}
	}

	/**
	* @brief Represents a Layout element, with it's type and name
	*/
	struct LayoutElement
	{
		/**
		* @brief Default constructor
		*/
		LayoutElement(DataType type, const std::string& name)
				: name(name), type(type), size(data_type_size(type)) {}

		/**
		* @brief Name of the element
		*/
		std::string	name				;

		/**
		* @brief DataType of the element
		*/
		DataType	type				;

		/**
		* @brief Size of the element in bytes
		*/
		uint32_t 	size				;

		/**
		* @brief Offset of the element in a Layout
		*/
		void* 		offset	{nullptr}	;

		/**
		* @brief Get the dimension of the data type. see data_type_dimension()
		*
		* @return 32 bits unsigned int representing the dimension of the data type
		*/
		[[nodiscard]] inline uint32_t getDimension() const
		{
			return data_type_dimension(type);
		}

		/**
		* @brief Get the OpenGL enum representing the data type. see data_type_gl_type()
		*
		* @return 32 bits unsigned int (synonym to GLenum) representing the OpenGL representation of the data type (GL_FLOAT..)
		*/
		[[nodiscard]] inline uint32_t getGLType() const
		{
			return data_type_gl_type(type);
		}
	};

	/**
	* @brief Layout used by shaders to know how to interpret the data in a Vertex Buffer
	*/
	class Layout
	{
	public:
		/**
		* @brief Default constructor takes a list of LayoutElement
		*
		* Use {} to create your own layouts
		*/
		Layout(std::initializer_list<LayoutElement> elements)
			: m_elements(elements)
		{
			calculate();
		}

		/**
		* @brief Get a list containing all of the LayoutElement
		*
		* @return Const reference to an std::list of LayoutElement
		*/
		[[nodiscard]] inline const std::list<LayoutElement>& getElements() const {return m_elements;}

		/**
		* @brief Get the size of one Vertex in a VBO in bytes (also called the stride)
		*
		* @return 32 bit unsigned integer representing the stride of the layout
		*/
		[[nodiscard]] inline uint32_t getStride() const {return m_stride;}

	private:
		std::list<LayoutElement> m_elements;
		uint32_t m_stride {0};

		void calculate();
	};
}
