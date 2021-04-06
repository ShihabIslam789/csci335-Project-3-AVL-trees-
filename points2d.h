// Shihab Islam
/* This program will take an array of integers to form coordinates
    such as the ones from graphs.This template will help print intergers
    print in that style of graphs.*/

#ifndef CSCI335_HOMEWORK2_POINTS2D_H_
#define CSCI335_HOMEWORK2_POINTS2D_H_

#include <array>
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>

namespace teaching_project {
    // Place comments that provide a brief explanation of this class,
    // and its sample usage.
    template<typename Object>
    class Points2D {
    public:
        // Default "big five" -- you have to alter them for your assignment.
        // That means that you will remove the "= default" statement.
        //  and you will provide an implementation for it.

        // Zero-parameter constructor. 
        // Set size to 0.
        Points2D() {
            size_ = 0;
            sequence_ = nullptr;
        }

        // Copy-constructor.
        Points2D(const Points2D& rhs) {
            size_ = rhs.size_;
            sequence_ = new std::array<Object, 2>[size_];
            for (int i{ 0 }; i < rhs.size(); ++i) {
                sequence_[i] = rhs[i];
            }
        }

        // Copy-assignment. If you have already written
        // the copy-constructor and the move-constructor
        // you can just use:
        // {
        // Points2D copy = rhs; 
        // std::swap(*this, copy);
        // return *this;
        // }
        Points2D& operator=(const Points2D& rhs) {
            Points2D copy = rhs;
            std::swap(*this, copy);
            return *this;
        }

        // Move-constructor. 
        Points2D(Points2D&& rhs) {
            this->sequence_ = rhs.sequence_;
            this->size_ = rhs.size_;
            rhs.size_ = 0;
            rhs.sequence_ = nullptr;
        }

        // Move-assignment.
        // Just use std::swap() for all variables.
        Points2D& operator=(Points2D&& rhs) {
            std::swap(size_, rhs.size_);
            std::swap(sequence_, rhs.sequence_);
            return *this;
        }
        ~Points2D() {
            delete[] sequence_;
        }

        // End of big-five.

        // One parameter constructor.
        Points2D(const std::array<Object, 2>& item) {
            size_ = 1;
            sequence_ = new std::array<Object, 2>{item};

        }

        // Read a chain from standard input.
        void ReadPoints2D() {
            // Part of code included (without error checking).
            std::string input_line;
            std::getline(std::cin, input_line);
            std::stringstream input_stream(input_line);
            if (input_line.empty())
                return;
            // Read size of sequence (an integer).
            int size_of_sequence;
            input_stream >> size_of_sequence;
            // Allocate space for sequence.
            size_ = size_of_sequence;
            sequence_ = new::std::array<Object, 2 >[size_of_sequence];

            Object token;
            for (int k{ 0 }; input_stream >> token; ++k) {
                // Read coordinates.
                int x = (k / 2); // x is from horizontal axis
                int y = (k % 2);// y is from vertical axis
                sequence_[x][y] = token;
            }
            std::cout << '\n'; // creates the proper spacing to read
        }

        size_t size() const {
            // just returns and prints the the current size
            return size_;
        }

        // @location: an index to a location in the given sequence.
        // @returns the point at @location.
        // const version.
        // abort() if out-of-range.
        const std::array<Object, 2>& operator[](size_t location) const {

            if (location < size_) {
                return sequence_[location];
            }
            abort(); // not in expected number range
        }

        //  @c1: A sequence.
        //  @c2: A second sequence.
        //  @return their sum. If the sequences are not of the same size, append the
        //    result with the remaining part of the larger sequence.
        friend Points2D operator+(const Points2D& c1, const Points2D& c2) {
            /* constantly loops through c1 and c2 to first find
             the sequences and then sum them in x+x and y+y */
            size_t size;
            Points2D<Object> sum;
            if (c1.size() > c2.size()) {
                size = c2.size();
                sum.size_ = c1.size();
                sum.sequence_ = new std::array<Object, 2>[sum.size_];
                sum = c1;
            }
            else {
                size = c1.size();
                sum.size_ = c2.size();
                sum.sequence_ = new std::array<Object, 2>[sum.size_];
                sum = c2;
            }
            for (int i{ 0 }; i < size; ++i) {
                sum.sequence_[i][0] = c1.sequence_[i][0] + c2.sequence_[i][0];
                sum.sequence_[i][1] = c1.sequence_[i][1] + c2.sequence_[i][1];
            }

            return sum;
        }

        // Overloading the << operator.
        friend std::ostream& operator<<(std::ostream& out, const Points2D& some_points2d) {
            // checks if empty, else we simply print what is in the operator
            if (some_points2d.size_ == 0) {
                out << "() ";

            }
            for (size_t i{ 0 }; i < some_points2d.size_; i++) {
                out << '(' << some_points2d[i][0] << ", " << some_points2d[i][1] << ") ";
            }
            out << std::endl;
            return out;
        }


    private:
        // Sequence of points. 
        std::array<Object, 2>* sequence_;
        // Size of the sequence.
        size_t size_;

    };

}  // namespace teaching_project
#endif // CSCI_335_HOMEWORK2_POINTS2D_H_