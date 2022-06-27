#pragma once
#ifndef _CUITOOLS_PROGRESSTEXT_HPP
#define _CUITOOLS_PROGRESSTEXT_HPP

#include "ChangableText.hpp"

namespace cuitools
{
    class ProgressText
    {
    private:
        using Self = cuitools::ProgressText;
    
        cuitools::ChangableText text_;
        std::size_t total_;
        std::size_t progress_;
    public:
    
        explicit ProgressText(std::size_t total)
            :text_()
            ,total_(total)
            ,progress_(0)
        {}
    
        ProgressText(const Self &other) = default;
    
        ProgressText(Self &&other) noexcept = default;
    
        inline Self &operator=(const Self &other)
        {
            if(this != std::addressof(other))
            {
                Self tmp{other};
                std::swap(tmp,*this);
            }
            return *this;
        }
    
        inline Self &operator=(Self &&other) noexcept
        {
            if(this != std::addressof(other))
            {
                this->text_ = std::move(other.text_);
                this->total_ = other.total_;
                this->progress_ = other.progress_;
            }
            return *this;
        }
    
        ~ProgressText() noexcept = default;
    
        inline const Self &Const() const noexcept
        {
            return *this;
        }

        inline std::size_t GetTotalProgress() const noexcept
        {
            return this->total_;
        }

        inline std::size_t GetProgress() const noexcept
        {
            return this->progress_;
        }

        inline void Show() noexcept
        {
            double total{static_cast<double>(this->total_)};
            double progress{this->progress_/total};
            progress *= 100;
            const char *format = "%.1lf%%";
            char buf[7] = {0};
            int len{std::snprintf(buf,sizeof(buf),format,progress)};
            if(len > 0)
            {
                this->text_.Write(buf,len);
            }
        }

        inline void Flush(std::size_t newProgress) noexcept
        {
            this->progress_ = newProgress;
            this->Show();
        }
    };
}

#endif