#pragma once
#ifndef _CUITOOLS_PROGRESSBOX_HPP
#define _CUITOOLS_PROGRESSBOX_HPP

#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <utility>

namespace cuitools
{
    class ProgressBox
    {
    private:
        using Self = cuitools::ProgressBox;
    
        std::size_t begin_;
        std::size_t end_;
        char leftBoundary_;
        char rightBoundary_;
        char completedMark_;
        char mark_;
        const char *title_;
        std::size_t titleSize_;
    public:
        explicit ProgressBox(std::size_t length)
            :ProgressBox(length,nullptr,0)
        {}

        ProgressBox(std::size_t length,const char *title,std::size_t titleSize)
            :begin_(0)
            ,end_(length + 1)
            ,leftBoundary_('[')
            ,rightBoundary_(']')
            ,completedMark_('>')
            ,mark_('=')
            ,title_(title)
            ,titleSize_(titleSize)
        {}
    
        ProgressBox(const Self &other) = default;
    
        ProgressBox(Self &&other) noexcept = default;
    
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

            }
            return *this;
        }
    
        ~ProgressBox() noexcept = default;
    
        inline const Self &Const() const noexcept
        {
            return *this;
        }

        inline char GetLeftBoundary() const noexcept
        {
            return this->leftBoundary_;
        }

        inline void SetLeftBoundary(char boundary) noexcept
        {
            this->leftBoundary_ = boundary;
        }

        inline char GetRightBoundary() const noexcept
        {
            return this->rightBoundary_;
        }

        inline void SetRightBoundary(char boundary) noexcept
        {
            this->rightBoundary_ = boundary;
        }

        inline char GetCompletedMark() const noexcept
        {
            return this->completedMark_;
        }

        inline void SetCompletedMark(char mark) noexcept
        {
            this->completedMark_ = mark;
        }

        inline char GetMark() const noexcept
        {
            return this->mark_;
        }

        inline void SetMark(char mark) noexcept
        {
            this->mark_ = mark;
        }

        inline const char *GetTitle() const noexcept
        {
            return this->title_;
        }

        inline std::size_t GetTitleSize() const noexcept
        {
            return this->titleSize_;
        }

        inline void SetTitle(const char *title,std::size_t titleSize) noexcept
        {
            this->title_ = title;
            this->titleSize_ = titleSize;
        }

        inline std::size_t GetSize() const noexcept
        {
            return this->end_ - 1;
        }

        inline void Show()
        {
            if(!this->begin_)
            {
                std::putchar(this->leftBoundary_);
                for(std::size_t i = 0,count = this->end_ - 1;i != count;++i)
                {
                    std::putchar(this->mark_);
                }
                std::putchar(this->rightBoundary_);
                if(this->title_)
                {
                    std::fputs(this->title_,stdout);
                }
                for(std::size_t i = 0,count = this->end_ - 1 + this->titleSize_;i != count;++i)
                {
                    std::putchar('\b');
                }
                this->begin_ += 1;
                std::fflush(stdout);
            }
        }

        inline void Flush(size_t newProgress)
        {
            newProgress += 1;
            for (;this->begin_ < newProgress;++this->begin_)
            {
                std::putchar(this->completedMark_);
            }
            if(newProgress == this->end_)
            {
                std::putchar(this->rightBoundary_);
                if(this->title_)
                {
                    std::fputs(this->title_,stdout);
                }
            }
            std::fflush(stdout);
        }

        inline void Reset()
        {
            this->begin_ = 0;
        }
    };
}

#endif