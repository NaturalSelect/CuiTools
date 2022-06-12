#pragma once
#ifndef _CUITOOLS_CHANGABLETEXT_HPP
#define _CUITOOLS_CHANGABLETEXT_HPP

#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <utility>

namespace cuitools
{
    class ChangableText
    {
    private:
        using Self = cuitools::ChangableText;
    
        std::size_t length_;
    public:
    
        ChangableText()
            :length_(0)
        {}
    
        ChangableText(const Self &other) = default;
    
        ChangableText(Self &&other) noexcept = default;
    
        inline Self &operator=(const Self &other)
        {
            Self tmp{other};
            std::swap(tmp,*this);
            return *this;
        }
    
        inline Self &operator=(Self &&other) noexcept
        {
            if(this != std::addressof(other))
            {
                this->length_ = other.length_;
            }
            return *this;
        }
    
        ~ChangableText() noexcept = default;
    
        inline const Self &Const() const noexcept
        {
            return *this;
        }

        inline void Clear() noexcept
        {
            for(std::size_t i = 0;i != this->length_;++i)
            {
                std::putchar('\b');
            }
            this->length_ = 0;
        }

        inline void Write(const char *text,std::size_t length) noexcept
        {
            std::size_t oldLength{this->length_};
            this->Clear();
            this->length_ = length;
            std::fputs(text,stdout);
            if(oldLength > length)
            {
                for(std::size_t i = length;i != oldLength;++i)
                {
                    std::putchar(' ');
                }
                for(std::size_t i = length;i != oldLength;++i)
                {
                    std::putchar('\b');
                }
            }
            std::fflush(stdout);
        }

        template<std::size_t _Size>
        inline void Write(const char (&text)[_Size])
        {
            this->Write(static_cast<const char*>(text),_Size - 1);
        }
    };
}

#endif