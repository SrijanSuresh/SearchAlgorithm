#include <gtest/gtest.h>

#include "search.h"
#include "tests/build_index.h"
#include "tests/clean_token.h"
#include "tests/find_query_matches.h"
#include "tests/gather_tokens.h"

// TODO_STUDENT: write your tests here!

TEST(CleanToken, ExampleEmptyTest) {
    //cout << "Hi! This shows up in the terminal." << endl;
    map<string, set<string>> tests;
    tests[""].insert("138918");
    tests[""].insert("");
}

// Test Case punctuation at both ends
TEST(CleanToken, BothEnds){
    map<string, set<string>> tests;

    tests["works"].insert("..works..");
    tests["works"].insert("..WORKS..");
    tests["works"].insert("#$Works$#");
    tests["works"].insert("works");

    testCleanToken(tests);

}

// Test Case punctuation in middle only, not either end
TEST(CleanToken, MiddleOnly){
    map<string, set<string>> tests;

    tests["wo-rks"].insert("wo-rks");
    tests["ab~cd"].insert("ab~cd");
    tests["wo$%#rks"].insert("wo$%#rks");
    tests["t#^&s"].insert("T#^&S");

    testCleanToken(tests);

}

// Test Case punctuation in middle, also at start (not end)

TEST(CleanToken, MiddleStart){
    map<string, set<string>> tests;

    tests["wo-rks"].insert("@wo-rks");
    tests["ab~cd"].insert("!@#ab~cd");
    tests["wo$%#rks"].insert("!@#wo$%#rks");
    tests["t#^&s"].insert("!@!T#^&S");

    testCleanToken(tests);

}

// Test Case punctuation in middle, also at end (not start)
TEST(CleanToken, MiddleEnd){
    map<string, set<string>> tests;

    tests["wo-rks"].insert("wo-rks@");
    tests["ab~cd"].insert("ab~cd!@#");
    tests["wo$%#rks"].insert("wo$%#rks!@#");
    tests["t#^&s"].insert("T#^&S!@!");

    testCleanToken(tests);

}

TEST(GatherTokens, SpaceAtBeginning) {
    string text = " &Th-is @is a $ sente!nce";
    set<string> expected = {"th-is", "is", "a", "sente!nce"};
    set<string> studentResult = gatherTokens(text);

    string testFeedback = "gatherTokens(\"" + text + "\") incorrect\n";

    EXPECT_EQ(expected, studentResult) << testFeedback;
}
TEST(GatherTokens, SpaceAtEnd) {
    string text = "&Th-is @is a $ sente!nce ";
    set<string> expected = {"th-is", "is", "a", "sente!nce"};
    set<string> studentResult = gatherTokens(text);

    string testFeedback = "gatherTokens(\"" + text + "\") incorrect\n";

    EXPECT_EQ(expected, studentResult) << testFeedback;
}

TEST(GatherTokens, MultipleSpaceBetween) {
    string text = "&Th-is @is a   $ sente!nce";
    set<string> expected = {"th-is", "is", "a", "sente!nce"};
    set<string> studentResult = gatherTokens(text);

    string testFeedback = "gatherTokens(\"" + text + "\") incorrect\n";

    EXPECT_EQ(expected, studentResult) << testFeedback;
}

/*TEST(FindQueryMatches, FirstNotInMap) {
    set<string> expected;

    expected = {};
    EXPECT_EQ(expected, findQueryMatches(INDEX, "firstone"));

    /*expected = {};
    EXPECT_EQ(expected, findQueryMatches(INDEX, "tthisis12 not in a map"));

    expected = {};
    EXPECT_EQ(expected, findQueryMatches(INDEX, "firstoneisa! ,empty &map"));

    expected = {};
    EXPECT_EQ(expected, findQueryMatches(INDEX, "!!addsome exclamat-ion!!"));

}
TEST(FindQueryMatches, LaterNotInMapPlus) {
    set<string> expected;

    expected = {};
    EXPECT_EQ(expected, findQueryMatches(INDEX, "hello +notinmap +to"));

    expected = {};
    EXPECT_EQ(expected, findQueryMatches(INDEX, "hello notinmap to"));

    expected = {};
    EXPECT_EQ(expected, findQueryMatches(INDEX, "!!addsome exclamat-ion!!"));

}
TEST(FindQueryMatches, LaterNotInMapMinus) {
    set<string> expected;

    expected = {};
    EXPECT_EQ(expected, findQueryMatches(INDEX, "firstone"));

    expected = {};
    EXPECT_EQ(expected, findQueryMatches(INDEX, "thisis12 not in a map"));

    expected = {};
    EXPECT_EQ(expected, findQueryMatches(INDEX, "firstoneisa! ,empty &map"));

    expected = {};
    EXPECT_EQ(expected, findQueryMatches(INDEX, "!!addsome exclamat-ion!!"));

}*/

TEST(BuildIndex, TinyTxt) {
    string filename = "tiny.txt";
    map<string, set<string>> expected = {
        {"eggs", {"www.shoppinglist.com"}},
        {"milk", {"www.shoppinglist.com"}},
        {"fish", {"www.shoppinglist.com","www.dr.seuss.net"}},
        {"bread", {"www.shoppinglist.com"}},
        {"cheese", {"www.shoppinglist.com"}},
        {"red", {"www.rainbow.org","www.dr.seuss.net"}},
        {"green", {"www.rainbow.org"}},
        {"orange", {"www.rainbow.org"}},
        {"yellow", {"www.rainbow.org"}},
        {"blue", {"www.rainbow.org","www.dr.seuss.net"}},
        {"indigo", {"www.rainbow.org"}},
        {"violet", {"www.rainbow.org"}},
        {"one", {"www.dr.seuss.net"}},
        {"two", {"www.dr.seuss.net"}},
        {"i'm", {"www.bigbadwolf.com"}},
        {"not", {"www.bigbadwolf.com"}},
        {"trying", {"www.bigbadwolf.com"}},
        {"to", {"www.bigbadwolf.com"}},
        {"eat", {"www.bigbadwolf.com"}},
        {"you", {"www.bigbadwolf.com"}},
    };
    map<string, set<string>> studentIndex;
    int studentNumProcesed = buildIndex(filename, studentIndex);

    string indexTestFeedback = "buildIndex(\"" + filename + "\", ...) index incorrect\n";
    EXPECT_EQ(expected, studentIndex) << indexTestFeedback;

    string retTestFeedback = "buildIndex(\"" + filename + "\", ...) return value incorrect\n";
    EXPECT_EQ(4, studentNumProcesed) << retTestFeedback;
}

TEST(BuildIndex, InvalidFilename) {
    string filename = "";
    map<string, set<string>> expected = {};
    map<string, set<string>> studentIndex;
    int studentNumProcesed = buildIndex(filename, studentIndex);

    string indexTestFeedback = "buildIndex(\"" + filename + "\", ...) index incorrect\n";
    EXPECT_EQ(expected, studentIndex) << indexTestFeedback;

    string retTestFeedback = "buildIndex(\"" + filename + "\", ...) return value incorrect\n";
    EXPECT_EQ(0, studentNumProcesed) << retTestFeedback;
}

TEST(FindQueryMatches, FirstTermNotInMap) {
    set<string> expected;

    expected = {"example.com", "uic.edu"};
    EXPECT_EQ(expected, findQueryMatches(INDEX, "firsttermhere hello here"));

    expected = {};
    EXPECT_EQ(expected, findQueryMatches(INDEX, "firstone"));

    expected = {};
    EXPECT_EQ(expected, findQueryMatches(INDEX, "firstoneisa! ,empty &map"));

    expected = {};
    EXPECT_EQ(expected, findQueryMatches(INDEX, "!!addsome exclamat-ion!!"));
}

TEST(FindQueryMatches, LaterTermWithPlusNotInMap) {
    set<string> expected;

    expected = {};
    EXPECT_EQ(expected, findQueryMatches(INDEX, "hello +lasterm"));
    expected = {};
    EXPECT_EQ(expected, findQueryMatches(INDEX, "I @am the! +lasterm"));
    expected = {};
    EXPECT_EQ(expected, findQueryMatches(INDEX, "HELLO +lasterm"));
}

TEST(FindQueryMatches, LaterTermWithMinusNotInMap) {
    set<string> expected;

    expected = { "example.com", "uic.edu" };
    EXPECT_EQ(expected, findQueryMatches(INDEX, "hello -lasterm"));
    expected = {};
    EXPECT_EQ(expected, findQueryMatches(INDEX, "I @am the! -lasterm"));
    expected = { "example.com", "uic.edu" };
    EXPECT_EQ(expected, findQueryMatches(INDEX, "HELLO -lasterm"));
}

TEST(FindQueryMatches, LaterTermUnmodifiedNotInMap) {
    set<string> expected;
    expected = { "example.com", "uic.edu" };
    EXPECT_EQ(expected, findQueryMatches(INDEX, "hello lastermworks"));
    expected = {};
    EXPECT_EQ(expected, findQueryMatches(INDEX, "I @am the! lasterm"));
    expected = { "example.com", "uic.edu" };
    EXPECT_EQ(expected, findQueryMatches(INDEX, "HELLO lasterm"));
}