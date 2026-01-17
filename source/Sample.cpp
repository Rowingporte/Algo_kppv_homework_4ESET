// arno qui fait

#include "Sample.h"

Sample::Sample(int tagValue, const vector<double>& featurevalues) : _tag(tagValue), _features(featureValues) {};

vector<double> Sample::get_features() const{
    return features;
};

int Sample::operator[](int index){
    return features[index];
};

int Sample::get_tag() const{
    return _tag;
};

void Sample::toString(Sample s) const{
    cout << "tag: " << s.tag() << endl;
};

Sample Sample::Scale(Sample s , double factor){
    vector<double> scaledFeatures;
    for(double feature : s.get_features()){
        scaledFeatures.push_back(feature * factor);
    }
    return Sample(s.get_tag(), scaledFeatures);
}
