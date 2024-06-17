# Enigma Machine
code is memory safe.

# Description

"[The Enigma machine](https://en.wikipedia.org/wiki/Enigma_machine#) is a cipher device developed and used in the early- to mid-20th century to protect commercial, diplomatic, and military communication." -- Wikipedia

- [Plugboard](https://en.wikipedia.org/wiki/Enigma_machine#Plugboard)
- [Reflector](https://en.wikipedia.org/wiki/Enigma_machine#Reflector)
- [Rotors](https://en.wikipedia.org/wiki/Enigma_rotor_details)

Everytime a letter is pressed, the rotor first ticks once.
You have to carefully connect the rotors such that when the notch of the previous one is hit, the later rotor tick as well. 
In another words, [turnover](https://en.wikipedia.org/wiki/Enigma_machine#Turnover) needs to be maintained carefully.
For Enigma I, each rotor only have one notch, so if the previous wheel turns by one circle (26 letters), the later should tick once.
But for Enigma M4, rotor VI to VIII has two notches, while rotor beta doesn't have notch, i.e. Beta never turns!

For the transformation part, the wiring of each rotor is fixed. 
Many of the commonly used rotors (I - VIII) has been set in `common.h`.
You can use [this page](https://www.cryptomuseum.com/crypto/enigma/wiring.htm) how the wiring works exactly.
You can also define your own rotors.

Finally, as a helper for debugging, this is an [online Enigma smiluator](https://cryptii.com/pipes/enigma-machine).
You can use it to encrypt many things.

## [Unit testing](https://en.wikipedia.org/wiki/Unit_testing)

I find some students don't test their code as much. 
Therefore, we use unit testing to do grading in this homework.
You are also encouraged to write your own unit testing to see if your code works.

The framework we use is [GoogleTest](http://google.github.io/googletest/primer.html).
GoogleTest is a C++ testing framework, but it also works in C, mostly. 
("mostly" contains too many corner cases where it is not the case. I don't want to go into that, you can [read it](https://en.wikipedia.org/wiki/Compatibility_of_C_and_C%2B%2B) yourself, but for our use case GoogleTest is good enough)
Don't panic.
I have already taken care of the C++ part.

To write a test, you only need to:

```cpp
TEST(<TestGroup>, <TestName>) {
    // Your test code.
    int my_result = 1;

    // The following command to test if you code is running correctly
    EXPECT_EQ(my_result, 1);
    EXPECT_TRUE(my_result == 1);

    // ASSERT halt program immediately on error. That means you won't have a change to clean up the memory, leak sanitizer may not be too happy about it.
    ASSERT_EQ(my_result, 1);

    // Remember to clean up your memory!
}
```

GoogleTest will compile all your tests into one single binary executable.
In this homework, it is `EnigmaTests`.
Running `EnigmaTests` will execute all tests you have.
You can also use filters to run only a handful of tests:

```sh
./EnigmaTests --gtest_filter=<regex>
```

GoogleTest will find names whose name matchs the [regular expression](https://en.wikipedia.org/wiki/Regular_expression) you provided.

As a result, this homework doesn't have example input and output as well. I wrote some unit tests for you, but that's it. You should come up with your own unit tests, and pass them before submitting.

## Debug mode

Some of you like to print the debug info to the screen, our autograder doesn't accept that.
Wouldn't it be nice if the printing works on your local machine, but doesn't execute on autograder?

Well, the answer is macro.

In `common.h` I defined a `DEBUGF`, you can use it as if `fprintf`. 
It prints to stderr, and only works when macro `DEBUG` is defined. There are two ways to define a macro `DEBUG`:

- Uncomment `common.h:11`, `#define DEBUG`. But that would mean any build will activate it.
- Pass it through cmake. Add `-DCMAKE_C_FLAGS=-DDEBUG -DCMAKE_CXX_FLAGS=-DDEBUG` when you are using cmake. It would define `DEBUG` when building.

# File structure

Here's how all the files are structured:

- `lib`. You can put all your implementation here.
- `include`. You can put all your definitions here. You are free to add stuff to `common.h` and `Enigma.h`, but DO NOT modify anything that's anything in it. Otherwise your code may not compile on autograder. `Enigma.h` contains detailed requirements for each function.
- `tests`. You can put any tests you wrote here. Changes to `AutograderTests.cpp` will be ignored. You are encouraged to pass `ExampleTests.cpp` before you submit.

1. Compiling your code with asan
2. Using GNU 11.3.0

# Enigma Machine structure

### Plugboard

Let's start with the easy part shall we? 
Plugboard is simple, it exchanges two letters, that's it.

When creating enigma `new_Enigma`, `size_t num_pairs` and `const char* pairs` is used to describe the pairs of letters that we want to exchange. You can assume `num_pairs` will be smaller than the buffer size of `pairs`.
If any configuration is wrong, you should return NULL.

Now that you've finished the plugboard, you can write tests to see if it works as you wish.
If it does, you can create an `Enigma`!
Although it still needs rotors and reflectors, you can put plugboard in the machine. You can do it by creating a field in `Enigma` that represent plugboard, and initialize it when `Enigma` is created.
This way, autograder can test if it works.

### Reflector

Reflector is more complicated than Plugboard. It shuffles the letters.
`const char* reflectors` in `new_Enigma` is used to describe it.
It will always (let's assume the user is sane enough) be a buffer of size 27. The buffer will describe how will the letter be shuffled. 
For example, if the 0-th char is `B`, that means `A` is shuffled to `B`

Again, test if your shuffle works on `I_UKW_A` listed in `common.h`.
Then put the reflector in your `Enigma`.

### Rotor initializion and setting

In `new_Enigma`, we provide you with the number of rotors (`size_t num_rotors`), a set of rotors (`const char** rotors`), and their initial settings (`size_t* inits`).
You can assume `num_rotors` is correct and won't cause overflow.
Each rotor is described using a null terminated string. The first 26 characters shows [the wiring](https://www.cryptomuseum.com/crypto/enigma/wiring.htm), followed by a comma, then the notchs location. As shown in `common.h`, a rotor may have multiple notches (VIII), or no notches (Beta). 

The actual machine has a small window to show the letter of the rotor. Let's call that setting (`inits`). Should you put multiple rotors in the machine, the user should be able to get the current setting. Therefore, please implement `get_setting_Enigma` first. You can assume the buffer provided is always valid.

The user should also be able to `reset_rotors_Enigma`. Enigma is symmetric. Reset the setting and type the encrypted message is how you do decryption. 


### Rotor tick

After each key press, the rotor turns once, or `tick`. After each `tick`, the setting changes accordingly. `tick_rotors_n_Enigma` press the keys of enigma for `n` times. Check how `tick` and notch works [here]((https://www.cryptomuseum.com/crypto/enigma/wiring.htm))

Hint: for `tick_rotors_n_Enigma`, do you really need to `tick` it n times, or can you compute the setting and then `reset_rotors_Enigma`?

### Rotor connect 

Let's not worry about the rings for now. The string described the mapping, like reflectors.
However, notice that rotors can be connected backwards. That means you need a revers look up: "For output X, what letter does the rotor converts to X?"
For the tests you write here, you can set `rings` to `A` to ignore the effect of rings.

Ring is an offset of the mapping. Imagine shifting the mapping by `ring` characters. Try to figure out (through the docs or simulator) how that would affect the encryption?

# Disclaimer

Engineerers often make the mistake called overengineering[[1](https://xkcd.com/974/), [2](https://en.wikipedia.org/wiki/Overengineering)]. 
For example, `Reflector` is just a `Rotor` that doesn't rotate. 
As a matter of fact, you probably realized that `Reflector`'s code look a lot alike `Rotor`, but simpler.

You can put rotor III, II, I, reflector UKW-B, and any number of cables in the plugboards, then you get an Enigma I.
You can also use rotor Beta and reflector UKW-C to make an Enigma M4 (Used by U-Boat)
You can even define your own rotors, and put any number of them in your machine to make it super complicated, the kind of machines that is never build, and probably will never be used.

# Source 
### Enigma Machine
https://www.youtube.com/watch?v=ybkkiGtJmkM

### Simulators 
https://legacy.cryptool.org/en/cto/enigma-step-by-step <br>
https://piotte13.github.io/enigma-cipher/
