#include "summarizationgenerator.h"
#include <QBitArray>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>

SummarizationGenerator::SummarizationGenerator()
{
}

QList<Summarization> SummarizationGenerator::generateAll(QList<Quantifier> &quantifierList, QMap<int, QList<const LinguisticValue *> > &linguisticValMap){

    QList<int> colNums = linguisticValMap.keys();

    QList<Summarization> summarizationList = QList<Summarization>();

    QBitArray selectedBitArray = QBitArray(linguisticValMap.size());
    while(selectedBitArray .count(true)<selectedBitArray .size()){
        for(int i = 0; i<selectedBitArray .size(); i++){
            selectedBitArray .toggleBit(i);
            if(selectedBitArray .testBit(i)){
                break;
            }
        }
        QList<int> selectedColNums  = QList<int>();
        for(int i =0; i<selectedBitArray.size(); i++){
            if(selectedBitArray.testBit(i)){
                selectedColNums.append(colNums.at(i));
            }
        }

        QBitArray bitArray = QBitArray(selectedColNums.size());

        //generowanie podzbiorow LinguisticValue
        while(bitArray.count(true)<bitArray.size()){
            for(int i = 0; i<bitArray.size(); i++){
                bitArray.toggleBit(i);
                if(bitArray.testBit(i)){
                    break;
                }
            }

            //generowanie wszystkich mozliwych podsumowan z list kwantyfikatorow, kwalifikatorow i sumaryzatorow
            QVector<int> indices = QVector<int>(selectedColNums.size());
            for(int i = 0; i< selectedColNums.size(); i++){
                indices[i] = linguisticValMap[selectedColNums.at(i)].size()-1;
            }


            while(indices[indices.size()-1]>=0){
                QList<const LinguisticValue *> summarizers = QList<const LinguisticValue *>();
                QList<const LinguisticValue *> qualifiers = QList<const LinguisticValue *>();

                for(int i = 0; i<indices.size(); i++){
                    int index = indices.at(i);
                    int key = selectedColNums.at(i);
                    if(bitArray.testBit(i)){
                        summarizers.append(linguisticValMap.value(key).at(index));
                    } else{
                        qualifiers.append(linguisticValMap.value(key).at(index));
                    }
                }

                for(int i = 0; i<quantifierList.size(); i++){
                    Summarization summarization = Summarization();
                    summarization.setSummarizers(summarizers);
                    summarization.setQualifiers(qualifiers);
                    summarization.setQuantifier(quantifierList.at(i));
                    summarizationList.append(summarization);
                }

                //aktualizacja indeksow:
                for(int i=0; i<indices.size(); i++){
                    indices[i]--;
                    if(i<indices.size()-1 && indices[i]<0){
                        indices[i] = linguisticValMap[selectedColNums.at(i)].size()-1;
                    }else{
                        break;
                    }
                }

            }
        }
    }

    return summarizationList;
}

void SummarizationGenerator::saveSummarizations(QList<QPair<double, Summarization> > summarizationMeasureList, QString filePath){
    QFile file(filePath);
    if(file.open(QIODevice::WriteOnly)){
        QTextStream out(&file);
        //QTextCodec *codec = QTextCodec::codecForUtfText("ąćęłńśóżź");
        //out.setCodec(codec);

        QList<const LinguisticValue *> summarizers;
        QList<const LinguisticValue *> qualifiers;
        Summarization summarization;

        for(int i=0; i<summarizationMeasureList.size(); i++){
            summarization = summarizationMeasureList.at(i).second;
            qualifiers = summarization.getQualifiers();
            summarizers = summarization.getSummarizers();

            out<<summarization.getQuantifier().getLabel()<<" pomiarow";
            if(!qualifiers.empty()){
                out<<" majacych";
                bool first = true;
                for(int j =0; j<qualifiers.size(); j++){
                    if(!first){
                        out<<" i "<<qualifiers.at(j)->getLabel();
                    }else{
                        out<<" "<<qualifiers.at(j)->getLabel();
                        first = false;
                    }
                }
                out<<" ma tez";
            } else{
                out<<" ma";
            }

            bool first = true;
            for(int j =0; j<summarizers.size(); j++){
                if(!first){
                    out<<" i "<<summarizers.at(j)->getLabel();
                }else{
                    out<<" "<<summarizers.at(j)->getLabel();
                    first = false;
                }
            }

            out<<". [Quality: "<<summarizationMeasureList.at(i).first<<"]"<<endl;
        }
    }
    file.close();
}
