#pragma once

#include "../theme/Theme.h"

#include <functional>
#include <optional>

namespace tng
{

// A caption and its value as bold text in an accent colour ("Step: 1/16"): drag the value
// up/down to step through values, or click it to pick from a list (Entry::list) or type a
// number (Entry::typed, for wide number ranges like MIDI's 0 to 127). The scroll wheel is
// left to the editor's scrolling.
class ValueBox final : public juce::Component
{
public:
    enum class Entry
    {
        list, // a click opens a list of every value: short sets of named choices
        typed, // a click opens a field to type into: numbers with a wide range
    };

    explicit ValueBox (juce::String caption);

    void setEntry (Entry newEntry);

    void setRange (int minimum, int maximum);
    void setValue (int newValue); // does not call onChange
    int getValue() const { return value; }

    std::function<juce::String (int)> toText = [] (int v) { return juce::String (v); };

    // Typed entry: the value meant by what was typed, or nothing to leave the value as it was.
    // By default, the number in the text.
    std::function<std::optional<int> (const juce::String&)> fromText = [] (const juce::String& text) -> std::optional<int> {
        if (! text.containsAnyOf ("0123456789"))
            return std::nullopt;
        return text.getIntValue();
    };
    std::function<void (int)> onChange;

    void setAccent (juce::Colour colour); // the value's colour

    // Shows this, muted, in place of the value, which then cannot be changed ("follows A").
    // Empty shows the value again.
    void setFixedText (const juce::String& text);

    // Just wide enough for the caption and the value shown (for typed entry, the widest value,
    // so the field has room and the row doesn't shift while dragging).
    int getPreferredWidth() const;

    // The value's hover backing reaches this far past its text.
    static constexpr int valueInset = 4;

    void paint (juce::Graphics& g) override;
    void mouseDown (const juce::MouseEvent& e) override;
    void mouseDrag (const juce::MouseEvent& e) override;
    void mouseUp (const juce::MouseEvent& e) override;
    void mouseMove (const juce::MouseEvent& e) override;
    void resized() override;

private:
    juce::Rectangle<int> valueArea() const; // the value's text, padded a little
    juce::String shownText() const;
    int captionWidth() const;
    void change (int newValue);
    void showList();
    void showField();
    void closeField (bool keep);
    int valueTextWidth() const; // room for the value's text

    juce::String caption;
    juce::String fixedText;
    juce::Colour accent;
    Entry entry = Entry::list;
    juce::TextEditor field;
    int value = 0, minValue = 0, maxValue = 1;
    int dragStartValue = 0;
    bool draggingValue = false;
};

} // namespace tng
