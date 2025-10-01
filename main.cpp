#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cassert>

int generateId () {
    int lastGenarted = 0;

    return ++lastGenarted;
}

using namespace std;
class Stream
{
    private:
      int id;
      double mass_flow;
      string name;
    public:
      Stream(){ id = generateId(); }
      void setMassFlow(double m) { mass_flow=m; }
      double getMassFlow() { return mass_flow; }
      void print(){ cout<<"Stream: "<<id<<", flow: "<<mass_flow<<endl; }
};

class Device
{
    protected:
      vector<shared_ptr<Stream>> inputs;
      vector<shared_ptr<Stream>> outputs;
    public:
      void addInput(shared_ptr<Stream> s){ inputs.push_back(s); }
      void addOutput(shared_ptr<Stream> s){ outputs.push_back(s); }
      virtual void updateOutputs() = 0;
};

class SimpleSeparator : public Device {
    private:
        double splittingRatio;

    public:
        SimpleSeparator(double ratio) : splittingRatio(ratio) {}

        void setSplittingRatio(double ratio) {
            splittingRatio = ratio;
        }

        double getSplittingRatio() {
            return splittingRatio;
        }

        void updateOutputs() override {
            if (inputs.size() < 1 || outputs.size() < 2) {
                cerr << "Not enough input or output streams are set for SimpleSeparator!" << endl;
                return;
            }

            double inputMassFlow = inputs[0]->getMassFlow();
            outputs[0]->setMassFlow(inputMassFlow * splittingRatio);
            outputs[1]->setMassFlow(inputMassFlow * (1 - splittingRatio));
        }
};

void testStream() {
    shared_ptr<Stream> testStream(new Stream());
    testStream->setMassFlow(20.0);
    assert(testStream->getMassFlow() == 20.0);
}

void testSimpleSeparator() {
    shared_ptr<Stream> s1(new Stream());
    s1->setMassFlow(10.0);

    shared_ptr<Stream> s2(new Stream());
    shared_ptr<Stream> s3(new Stream());

    SimpleSeparator separator(0.5);
    assert(separator.getSplittingRatio() == 0.5);

    separator.addInput(s1);
    separator.addOutput(s2);
    separator.addOutput(s3);

    separator.updateOutputs();

    assert(s2->getMassFlow() == 5.0);
    assert(s3->getMassFlow() == 5.0);
}

void runTests () {
    testStream();
    testSimpleSeparator();
}

int main() {
    shared_ptr<Stream> s1(new Stream());
    shared_ptr<Stream> s2(new Stream());
    shared_ptr<Stream> s3(new Stream());

    s1->setMassFlow(15.0);

    SimpleSeparator separator(0.6);
    separator.addInput(s1);
    separator.addOutput(s2);
    separator.addOutput(s3);

    separator.updateOutputs();

    s1->print();
    s2->print();
    s3->print();

    runTests();

    return 0;
}