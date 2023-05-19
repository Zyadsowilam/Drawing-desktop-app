#include <QVTKOpenGLNativeWidget.h>
#include <vtkActor.h>
#include <vtkDataSetMapper.h>
#include <vtkDoubleArray.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkPointData.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>

#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkPolygon.h> 

#include <vtkLineSource.h>
#include <vtkPointPicker.h>
#include <vtkRendererCollection.h>
#include <vtkPolyDataMapper.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>
#include <vtkTextRepresentation.h>
#include <vtkTextWidget.h>
#include <vtkCamera.h>
#include <vtkLine.h>
#include <vtkTransform.h>

#include <QApplication>
#include <vtkActor.h>
#include <vtkDataSetMapper.h>
#include <vtkDoubleArray.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkPointData.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>

#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkPolygon.h> 

#include <vtkLineSource.h>

#include <vtkPointPicker.h>
#include <vtkRendererCollection.h>
#include <vtkPolyDataMapper.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>
#include <vtkTextRepresentation.h>
#include <vtkCamera.h>
#include <vtkLine.h>
#include <vtkTransform.h>
#include<QScrollArea.h>
#include <QApplication>
#include <QDockWidget>
#include <QGridLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPointer>
#include <QPushButton>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QFileDialog>
#include <QComboBox>
#include <QColorDialog>

#include <cmath>
#include <cstdlib>
#include <random>
#include <iostream>
#include <fstream>
using namespace std;

std::vector<vtkActor*> actors;

ofstream myfile;
ifstream readfile;
int filecounter = 0;
std::vector<vtkActor*> lineActors;
std::vector<std::pair<vtkLineSource*, vtkActor*>> lines;
std::vector<std::pair<vtkSmartPointer<vtkPolygon>, vtkSmartPointer<vtkActor>>> polygons;
int ILine = 0;
int ICircle = 0;
int wCircle = 0;
int IArc = 0;
int IPolygon = 0;
int IHeart = 0;
int IEllipse = 0;
int IStar = 0;
int IRight = 0;
int ISphere = 0;
int ICube = 0;
int IEllipsoid = 0;

std::set<QString> drawnshapes;


std::map<int, std::vector<std::string>> circleData;


namespace {
    // Define interaction style
    class customMouseInteractorStyle : public vtkInteractorStyleTrackballCamera
    {
    /*public:

        static customMouseInteractorStyle* New();
        vtkTypeMacro(customMouseInteractorStyle, vtkInteractorStyleTrackballCamera);

        virtual void OnLeftButtonDown() override
        {
            click++;
            vtkRenderWindowInteractor* interactor = this->Interactor;
            if (click == 1) {
                this->Interactor->GetPicker()->Pick(this->Interactor->GetEventPosition()[0],//pick the first point using mouse x&y
                    this->Interactor->GetEventPosition()[1],
                    0, // always zero.
                    this->Interactor->GetRenderWindow()
                    ->GetRenderers()
                    ->GetFirstRenderer());//The renderer in which the picking operation will be performed.
                double pickedone[3];
                this->Interactor->GetPicker()->GetPickPosition(pickedone);
                UpdateFirstPoint(pickedone);
            }
            if (click == 2) {
                double pickedtwo[3];
                this->Interactor->GetPicker()->GetPickPosition(pickedtwo);
                vtkRenderWindowInteractor* interactor = this->Interactor;
                this->Interactor->GetPicker()->Pick(this->Interactor->GetEventPosition()[0],//pick the first point using mouse x&y
                    this->Interactor->GetEventPosition()[1],
                    0, // always zero.
                    this->Interactor->GetRenderWindow()
                    ->GetRenderers()
                    ->GetFirstRenderer());//The renderer in which the picking operation will be performed.
                UpdateSecondPoint(pickedtwo);
                click = 0;
            }
            double* point1 = LineSource->GetPoint1();
            double* point2 = LineSource->GetPoint2();
            char text[100];
            sprintf(text, "Line coordinates: (%.2f, %.2f) - (%.2f, %.2f)", point1[0], point1[1], point2[0], point2[1]);
            TextActor->SetInput(text);
            TextActor->Modified();
            //writeInFile();
            // Forward events
            vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
        }
        void setLineSource(vtkLineSource* linesource) {
            this->LineSource = linesource;
        }
        void setTextActor(vtkTextActor* actor) {
            TextActor = actor;
        }
        void UpdateFirstPoint(double* pickedone) {
            LineSource->SetPoint1(pickedone[0], pickedone[1], pickedone[2]);
        }
        void UpdateSecondPoint(double* pickedtwo) {
            LineSource->SetPoint2(pickedtwo[0], pickedtwo[1], pickedtwo[2]);
        }
        void setVTKActor(vtkActor* lineActor) {
            this->lineActor = lineActor;
        }

    private:
        vtkLineSource* LineSource;
        vtkTextActor* TextActor;
        vtkActor* lineActor;
        int click = 0;*/
    };
    /*vtkStandardNewMacro(customMouseInteractorStyle);*/

    //-------------------------------------------------------------------------------------------------------------------------------------------
    void writeInFile() {
        QString fileName = QFileDialog::getSaveFileName(nullptr, "Save File", ".", "Text Files (*.txt)");
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);

            // Loop through all lines and polygons in vectors
/* or (auto line : lines) {

                double* point1 = line.first->GetPoint1();
                double* point2 = line.first->GetPoint2();
                out << "L " << point1[0] << " " << point1[1] << " "; // write line data to the file
                out << point2[0] << " " << point2[1] << " ";
                out << line.second->GetProperty()->GetColor()[0] << " "
                    << line.second->GetProperty()->GetColor()[1] << " "
                    << line.second->GetProperty()->GetColor()[2] << " ";
                out << line.second->GetProperty()->GetLineWidth() << Qt::endl;
            }

            for (auto poly : polygons) {
                vtkPoints* points = poly.first->GetPoints();
                vtkIdType numPoints = points->GetNumberOfPoints();
                out << "P " << numPoints << " "; // write polygon data to the file
                for (vtkIdType i = 0; i < numPoints; i++) {
                    double* point = points->GetPoint(i);
                    out << point[0] << " " << point[1] << " ";
                }
                out << poly.second->GetProperty()->GetColor()[0] << " "
                    << poly.second->GetProperty()->GetColor()[1] << " "
                    << poly.second->GetProperty()->GetColor()[2] << " ";
                out << poly.second->GetProperty()->GetLineWidth() << Qt::endl;
            }*/
         

            for (const auto& entry : circleData) {
                int circleIndex = entry.first;
                const std::vector<std::string>& values = entry.second;

                

                // Write the values
                for (const std::string& value : values) {
                    out << QString::fromStdString(value) << " ";
                }

                out << Qt::endl;
            }
            /*  for (const QString& data : circleData) {
                if (count == 0) {
                    out << "C ";
                }
               

                out << data << " ";

                count++;
                if (count % 8 == 0) {
                    out << Qt::endl;
                }
            }*/


            file.close();
        }
    }





    void updateTextCoordinates(vtkLineSource* linesource, vtkTextActor* TextActor, vtkActor* lineActor) {
        double* point1 = linesource->GetPoint1();
        double* point2 = linesource->GetPoint2();
        char text[100];
        sprintf(text, "Line coordinates: (%.2f, %.2f) - (%.2f, %.2f)", point1[0], point1[1], point2[0], point2[1]);
        TextActor->SetInput(text);
        TextActor->Modified();
    }
    void updateLineComboBox(QComboBox& lineComboBox) {
        lineComboBox.clear();
        for (int i = 0; i < lineActors.size(); ++i) {
            QString lineName = "line" + QString::number(i);
            lineComboBox.addItem(lineName);
        }
        lineComboBox.update();
    }
    void drawLine(vtkRenderer* renderer, vtkGenericOpenGLRenderWindow* window, vtkTextActor* textActor, QComboBox& lineComboBox) {
        double x1 = QInputDialog::getDouble(NULL, "Enter first coordinates", "x1 coordinate", 0, -1000, 1000, 2);
        double y1 = QInputDialog::getDouble(NULL, "Enter first coordinates", "y1 coordinate", 0, -1000, 1000, 2);
        double x2 = QInputDialog::getDouble(NULL, "Enter second coordinates", "x2 coordinate", 0, -1000, 1000, 2);
        double y2 = QInputDialog::getDouble(NULL, "Enter second coordinates", "y2 coordinate", 0, -1000, 1000, 2);

        vtkLineSource* lineSource = vtkLineSource::New();
        lineSource->SetPoint1(x1, y1, 0.0);
        lineSource->SetPoint2(x2, y2, 0.0);
        lineSource->Update();

        vtkPolyDataMapper* mapper = vtkPolyDataMapper::New();
        mapper->SetInputConnection(lineSource->GetOutputPort());

        vtkActor* lineActor = vtkActor::New();
        lineActor->SetMapper(mapper);
        lineActor->GetProperty()->SetColor(1.0, 0.0, 0.0); // Set line color to red

        renderer->AddActor(lineActor);
        updateTextCoordinates(lineSource, textActor, lineActor);

        // Set the camera to show all actors in the scene
        vtkCamera* camera = renderer->GetActiveCamera();
        double* bounds = renderer->ComputeVisiblePropBounds();
        double diagonal = sqrt(vtkMath::Distance2BetweenPoints(bounds, bounds + 1) +
            vtkMath::Distance2BetweenPoints(bounds + 2, bounds + 3) +
            vtkMath::Distance2BetweenPoints(bounds + 4, bounds + 5));
        double centerX = (bounds[0] + bounds[1]) / 2.0;
        double centerY = (bounds[2] + bounds[3]) / 2.0;
        double centerZ = (bounds[4] + bounds[5]) / 2.0;
        camera->SetFocalPoint(centerX, centerY, centerZ);
        camera->SetPosition(centerX, centerY, centerZ + diagonal);
        camera->SetViewUp(0, 1, 0);
        renderer->ResetCameraClippingRange();

        QColorDialog colorDialog;
        if (colorDialog.exec() == QDialog::Accepted) {
            QColor color = colorDialog.currentColor();
            int red = color.red();
            int green = color.green();
            int blue = color.blue();
            lineActor->GetProperty()->SetColor(red, green, blue);
        }

        double lineWidth = QInputDialog::getDouble(NULL, "Enter line width", "Line width", 1.0, 0.1, 10.0, 2);
        lineActor->GetProperty()->SetLineWidth(lineWidth);
        QStringList lineStyles;
        lineStyles << "Solid" << "Dashed" << "Dotted";
        QString selectedLineStyle = QInputDialog::getItem(NULL, "Select line style", "Line style", lineStyles, 0);
        vtkProperty* lineProperty = lineActor->GetProperty();
        if (selectedLineStyle == "Dashed") {
            lineProperty->SetLineStipplePattern(0xf0f0);
            lineProperty->SetLineStippleRepeatFactor(5); // Set repeat factor to 5
        }
        else if (selectedLineStyle == "Dotted") {
            lineProperty->SetLineStipplePattern(0x00ff);
            lineProperty->SetLineStippleRepeatFactor(5); // Set repeat factor to 5
        }
        else {
            lineProperty->SetLineStipplePattern(0xffff);
            lineProperty->SetLineStippleRepeatFactor(1); // Set repeat factor to 1
        }


        lines.push_back(std::make_pair(lineSource, lineActor));
        actors.push_back(lineActor);

        drawnshapes.insert("Line " + QString::number(ILine));
        ILine++;
        window->Render();
    }
    void drawLineee(vtkRenderer* renderer, vtkGenericOpenGLRenderWindow* window, vtkTextActor* textActor, double x1, double y1, double x2, double y2, double red, double green, double blue, double lineWidth) {


        vtkLineSource* lineSource = vtkLineSource::New();
        lineSource->SetPoint1(x1, y1, 0.0);
        lineSource->SetPoint2(x2, y2, 0.0);
        lineSource->Update();

        vtkPolyDataMapper* mapper = vtkPolyDataMapper::New();
        mapper->SetInputConnection(lineSource->GetOutputPort());

        vtkActor* lineActor = vtkActor::New();
        lineActor->SetMapper(mapper);
        lineActor->GetProperty()->SetColor(1.0, 0.0, 0.0); // Set line color to red

        renderer->AddActor(lineActor);
        updateTextCoordinates(lineSource, textActor, lineActor);

        // Set the camera to show all actors in the scene
        vtkCamera* camera = renderer->GetActiveCamera();
        double* bounds = renderer->ComputeVisiblePropBounds();
        double diagonal = sqrt(vtkMath::Distance2BetweenPoints(bounds, bounds + 1) +
            vtkMath::Distance2BetweenPoints(bounds + 2, bounds + 3) +
            vtkMath::Distance2BetweenPoints(bounds + 4, bounds + 5));
        double centerX = (bounds[0] + bounds[1]) / 2.0;
        double centerY = (bounds[2] + bounds[3]) / 2.0;
        double centerZ = (bounds[4] + bounds[5]) / 2.0;
        camera->SetFocalPoint(centerX, centerY, centerZ);
        camera->SetPosition(centerX, centerY, centerZ + diagonal);
        camera->SetViewUp(0, 1, 0);
        renderer->ResetCameraClippingRange();


        lineActor->GetProperty()->SetColor(red, green, blue);



        lineActor->GetProperty()->SetLineWidth(lineWidth);




        lines.push_back(std::make_pair(lineSource, lineActor));
        actors.push_back(lineActor);

        drawnshapes.insert("Line " + QString::number(ILine));
        ILine++;
        window->Render();
    }
    void drawPolgn(vtkRenderer* renderer, vtkGenericOpenGLRenderWindow* window, vtkTextActor* textActor) {
        int n = QInputDialog::getInt(NULL, "Enter integer value", "Value:", 1, 3, 1000, 1);

        std::vector<double> x(n);
        std::vector<double> y(n);

        for (int i = 0; i < n; i++) {
            QString label = QString("Enter point %1 coordinates").arg(i + 1);
            x[i] = QInputDialog::getDouble(NULL, label, "x coordinate", 0, -1000, 1000, 2);
            y[i] = QInputDialog::getDouble(NULL, label, "y coordinate", 0, -1000, 1000, 2);
        }

        vtkPoints* points = vtkPoints::New();
        for (int i = 0; i < n; i++) {
            points->InsertNextPoint(x[i], y[i], 0.0);
        }

        vtkCellArray* lines = vtkCellArray::New();
        for (int i = 0; i < n - 1; i++) {
            vtkLine* line = vtkLine::New();
            line->GetPointIds()->SetId(0, i);
            line->GetPointIds()->SetId(1, i + 1);
            lines->InsertNextCell(line);
            line->Delete();
        }
        // Close the polygon
        vtkLine* line = vtkLine::New();
        line->GetPointIds()->SetId(0, n - 1);
        line->GetPointIds()->SetId(1, 0);
        lines->InsertNextCell(line);
        line->Delete();

        vtkPolyData* polyData = vtkPolyData::New();
        polyData->SetPoints(points);
        polyData->SetLines(lines);

        vtkPolyDataMapper* mapper = vtkPolyDataMapper::New();
        mapper->SetInputData(polyData);

        vtkActor* actor = vtkActor::New();
        actor->SetMapper(mapper);
        actor->GetProperty()->SetColor(1.0, 0.0, 0.0); // Set line color to red

        renderer->AddActor(actor);


        // Set the camera to show all actors in the scene
        vtkCamera* camera = renderer->GetActiveCamera();
        double* bounds = renderer->ComputeVisiblePropBounds();
        double diagonal = sqrt(vtkMath::Distance2BetweenPoints(bounds, bounds + 1) +
            vtkMath::Distance2BetweenPoints(bounds + 2, bounds + 3) +
            vtkMath::Distance2BetweenPoints(bounds + 4, bounds + 5));
        double centerX = (bounds[0] + bounds[1]) / 2.0;
        double centerY = (bounds[2] + bounds[3]) / 2.0;
        double centerZ = (bounds[4] + bounds[5]) / 2.0;
        camera->SetFocalPoint(centerX, centerY, centerZ);
        camera->SetPosition(centerX, centerY, centerZ + diagonal);
        camera->SetViewUp(0, 1, 0);
        renderer->ResetCameraClippingRange();

        QColorDialog colorDialog;
        if (colorDialog.exec() == QDialog::Accepted) {
            QColor color = colorDialog.currentColor();
            int red = color.red();
            int green = color.green();
            int blue = color.blue();
            actor->GetProperty()->SetColor(red, green, blue);
            // Set line color to the color selected from the color dialog
        }
        drawnshapes.insert("Polygon " + QString::number(IPolygon));
        IPolygon++;
        window->Render();

        // Clean up
        points->Delete();
        lines->Delete();
        polyData->Delete();
        mapper->Delete();
        actor->Delete();
        actors.push_back(actor);
    }

    void drawPolygon(vtkRenderer* renderer, vtkGenericOpenGLRenderWindow* window, vtkTextActor* textActor) {
        double centerX = QInputDialog::getDouble(NULL, "Enter center coordinates", "x coordinate", 0, -1000, 1000, 2);
        double centerY = QInputDialog::getDouble(NULL, "Enter center coordinates", "y coordinate", 0, -1000, 1000, 2);
        int numSides = QInputDialog::getInt(NULL, "Enter number of sides", "Number of sides", 3, 3, 100);
        double radius = QInputDialog::getDouble(NULL, "Enter radius", "Radius", 1.0, 0.1, 100.0, 2);

        vtkPoints* points = vtkPoints::New();
        vtkCellArray* lines = vtkCellArray::New();
        for (int i = 0; i < numSides; i++) {
            double angle = 2.0 * vtkMath::Pi() * i / numSides;
            double x = centerX + radius * cos(angle);
            double y = centerY + radius * sin(angle);
            points->InsertNextPoint(x, y, 0.0);
        }
        for (int i = 0; i < numSides - 1; i++) {
            vtkLine* line = vtkLine::New();
            line->GetPointIds()->SetId(0, i);
            line->GetPointIds()->SetId(1, i + 1);
            lines->InsertNextCell(line);
        }
        vtkLine* line = vtkLine::New();
        line->GetPointIds()->SetId(0, numSides - 1);
        line->GetPointIds()->SetId(1, 0);
        lines->InsertNextCell(line);

        vtkPolyData* polyData = vtkPolyData::New();
        polyData->SetPoints(points);
        polyData->SetLines(lines);

        vtkPolyDataMapper* mapper = vtkPolyDataMapper::New();
        mapper->SetInputData(polyData);

        vtkActor* actor = vtkActor::New();
        actor->SetMapper(mapper);

        QColorDialog colorDialog;
        if (colorDialog.exec() == QDialog::Accepted) {
            QColor color = colorDialog.currentColor();
            int red = color.red();
            int green = color.green();
            int blue = color.blue();
            actor->GetProperty()->SetColor(red, green, blue);
        }

        double lineWidth = QInputDialog::getDouble(NULL, "Enter line width", "Line width", 1.0, 0.1, 10.0, 2);
        actor->GetProperty()->SetLineWidth(lineWidth);

        renderer->AddActor(actor);

        // Create a pair of vtkPolygon and vtkActor objects and add them to the polygons vector
        vtkPolygon* polygon = vtkPolygon::New();
        polygon->GetPointIds()->SetNumberOfIds(numSides);
        for (int i = 0; i < numSides; i++) {
            polygon->GetPointIds()->SetId(i, i);
        }
        polygons.push_back(std::make_pair(vtkSmartPointer < vtkPolygon>::Take(polygon), vtkSmartPointer<vtkActor>::Take(actor)));
        std::string numPolygonsStr = "Number of polygons: " + std::to_string(polygons.size());
        drawnshapes.insert("Right Polygon " + QString::number(IRight));
        IRight++;
        textActor->SetInput(numPolygonsStr.c_str());
        renderer->ResetCamera();
        actors.push_back(actor);
        window->Render();


    }

    void drawStar(vtkRenderer* renderer, vtkGenericOpenGLRenderWindow* window, vtkTextActor* textActor) {
        double centerX = QInputDialog::getDouble(NULL, "Enter center coordinates", "x coordinate", 0, -1000, 1000, 2);
        double centerY = QInputDialog::getDouble(NULL, "Enter center coordinates", "y coordinate", 0, -1000, 1000, 2);
        double radius = QInputDialog::getDouble(NULL, "Enter radius", "Radius", 1.0, 0.1, 100.0, 2);
        int numPoints = QInputDialog::getInt(NULL, "Enter number of points", "Number of points", 5, 3, 100, 1);

        vtkPoints* points = vtkPoints::New();
        vtkCellArray* lines = vtkCellArray::New();
        double angle = 0.0;
        double angleStep = 2.0 * vtkMath::Pi() / numPoints;
        for (int i = 0; i < numPoints; i++) {
            double x = centerX + radius * cos(angle);
            double y = centerY + radius * sin(angle);
            points->InsertNextPoint(x, y, 0.0);

            vtkLine* line = vtkLine::New();
            line->GetPointIds()->SetId(0, i);
            line->GetPointIds()->SetId(1, (i + numPoints / 2) % numPoints);
            lines->InsertNextCell(line);

            angle += angleStep;
        }

        vtkPolyData* polyData = vtkPolyData::New();
        polyData->SetPoints(points);
        polyData->SetLines(lines);

        vtkPolyDataMapper* mapper = vtkPolyDataMapper::New();
        mapper->SetInputData(polyData);

        vtkActor* actor = vtkActor::New();
        actor->SetMapper(mapper);

        QColorDialog colorDialog;
        if (colorDialog.exec() == QDialog::Accepted) {
            QColor color = colorDialog.currentColor();
            int red = color.red();
            int green = color.green();
            int blue = color.blue();
            actor->GetProperty()->SetColor(red, green, blue);
        }

        double lineWidth = QInputDialog::getDouble(NULL, "Enter line width", "Line width", 1.0, 0.1, 10.0, 2);
        actor->GetProperty()->SetLineWidth(lineWidth);
        drawnshapes.insert("Star " + QString::number(IStar));
        IStar++;
        renderer->AddActor(actor);
        actors.push_back(actor);
        renderer->ResetCamera();
        window->Render();
    }

    void drawCircle(vtkRenderer* renderer, vtkGenericOpenGLRenderWindow* window, vtkTextActor* textActor) {
        double centerX = QInputDialog::getDouble(NULL, "Enter center coordinates", "x coordinate", 0, -1000, 1000, 2);
        double centerY = QInputDialog::getDouble(NULL, "Enter center coordinates", "y coordinate", 0, -1000, 1000, 2);
        int numSides = 100;
        double radius = QInputDialog::getDouble(NULL, "Enter radius", "Radius", 1.0, 0.1, 100.0, 2);
        std::string strCenterX = std::to_string(centerX);
        std::string strCenterY = std::to_string(centerY);
        std::string strRadius = std::to_string(radius);

        vtkPoints* points = vtkPoints::New();
        vtkCellArray* lines = vtkCellArray::New();
        for (int i = 0; i < numSides; i++) {
            double angle = 2.0 * vtkMath::Pi() * i / numSides;
            double x = centerX + radius * cos(angle);
            double y = centerY + radius * sin(angle);
            points->InsertNextPoint(x, y, 0.0);
        }
        for (int i = 0; i < numSides - 1; i++) {
            vtkLine* line = vtkLine::New();
            line->GetPointIds()->SetId(0, i);
            line->GetPointIds()->SetId(1, i + 1);
            lines->InsertNextCell(line);
        }
        vtkLine* line = vtkLine::New();
        line->GetPointIds()->SetId(0, numSides - 1);
        line->GetPointIds()->SetId(1, 0);
        lines->InsertNextCell(line);

        vtkPolyData* polyData = vtkPolyData::New();
        polyData->SetPoints(points);
        polyData->SetLines(lines);

        vtkPolyDataMapper* mapper = vtkPolyDataMapper::New();
        mapper->SetInputData(polyData);

        vtkActor* actor = vtkActor::New();
        actor->SetMapper(mapper);
        double re = 0;
        double ge = 0;
        double be = 0;

        QColorDialog colorDialog;
        if (colorDialog.exec() == QDialog::Accepted) {
            QColor color = colorDialog.currentColor();
            double red = color.redF();
            double green = color.greenF();
            double blue = color.blueF();
            re = red;
            ge = green;
            be = blue;
            actor->GetProperty()->SetColor(red, green, blue);


        }

        std::string strre = std::to_string(re);
        std::string strge = std::to_string(ge);
        std::string strbe = std::to_string(be);
        double lineWidth = QInputDialog::getDouble(NULL, "Enter line width", "Line width", 1.0, 0.1, 10.0, 2);
        actor->GetProperty()->SetLineWidth(lineWidth);
        std::string strlineWidth = std::to_string(lineWidth);
        renderer->AddActor(actor);

        // Create a pair of vtkPolygon and vtkActor objects and add them to the polygons vector
        vtkPolygon* polygon = vtkPolygon::New();
        polygon->GetPointIds()->SetNumberOfIds(numSides);
        for (int i = 0; i < numSides; i++) {
            polygon->GetPointIds()->SetId(i, i);
        }
      
       
        circleData[wCircle] = { "c", strCenterX, strCenterY, strRadius, strre, strge, strbe, strlineWidth,"p"};
        for (const std::string& value : circleData[wCircle]) {
            std::cout << value << " ";
        }
         drawnshapes.insert("Circle " + QString::number(ICircle));
        ICircle++;
        wCircle++;
       
        renderer->AddActor(actor);
        actors.push_back(actor);
        renderer->ResetCamera();
        window->Render();
    } 
    
   
    void drawCircleread(vtkRenderer* renderer, vtkGenericOpenGLRenderWindow* window, vtkTextActor* textActor, double centerX, double centerY, double radius, double red, double green, double blue, double lineWidth) {
        
        int numSides = 100;
        

        vtkPoints* points = vtkPoints::New();
        vtkCellArray* lines = vtkCellArray::New();
        for (int i = 0; i < numSides; i++) {
            double angle = 2.0 * vtkMath::Pi() * i / numSides;
            double x = centerX + radius * cos(angle);
            double y = centerY + radius * sin(angle);
            points->InsertNextPoint(x, y, 0.0);
        }
        for (int i = 0; i < numSides - 1; i++) {
            vtkLine* line = vtkLine::New();
            line->GetPointIds()->SetId(0, i);
            line->GetPointIds()->SetId(1, i + 1);
            lines->InsertNextCell(line);
        }
        vtkLine* line = vtkLine::New();
        line->GetPointIds()->SetId(0, numSides - 1);
        line->GetPointIds()->SetId(1, 0);
        lines->InsertNextCell(line);

        vtkPolyData* polyData = vtkPolyData::New();
        polyData->SetPoints(points);
        polyData->SetLines(lines);

        vtkPolyDataMapper* mapper = vtkPolyDataMapper::New();
        mapper->SetInputData(polyData);

        vtkActor* actor = vtkActor::New();
        actor->SetMapper(mapper);

      
            actor->GetProperty()->SetColor(red, green, blue);
         /* circleData.insert(QString::number(centerX));
            circleData.insert(QString::number(centerY));
            circleData.insert(QString::number(radius));
            circleData.insert(QString::number(red));
            circleData.insert(QString::number(green));
            circleData.insert(QString::number(blue));*/
        
        actor->GetProperty()->SetLineWidth(lineWidth);
      //circleData.insert(QString::number(lineWidth));
        renderer->AddActor(actor);

        // Create a pair of vtkPolygon and vtkActor objects and add them to the polygons vector
        vtkPolygon* polygon = vtkPolygon::New();
        polygon->GetPointIds()->SetNumberOfIds(numSides);
        for (int i = 0; i < numSides; i++) {
            polygon->GetPointIds()->SetId(i, i);
        }
       
        ICircle++;
        
       
        renderer->ResetCamera();
        window->Render();
    }
    void drawSphere(vtkRenderer* renderer, vtkGenericOpenGLRenderWindow* window, vtkTextActor* textActor) {
        double centerX = QInputDialog::getDouble(NULL, "Enter center coordinates", "x coordinate", 0, -1000, 1000, 2);
        double centerY = QInputDialog::getDouble(NULL, "Enter center coordinates", "y coordinate", 0, -1000, 1000, 2);
        double centerZ = QInputDialog::getDouble(NULL, "Enter center coordinates", "z coordinate", 0, -1000, 1000, 2);
        int numSides = 1000;
        int numSegments = 100;
        double radius = QInputDialog::getDouble(NULL, "Enter radius", "Radius", 1.0, 0.1, 100.0, 2);

        vtkPoints* points = vtkPoints::New();
        vtkCellArray* lines = vtkCellArray::New();
        for (int i = 0; i <= numSegments; i++) {
            double theta1 = vtkMath::Pi() * i / numSegments;
            double sinTheta1 = sin(theta1);
            double cosTheta1 = cos(theta1);

            for (int j = 0; j < numSides; j++) {
                double phi = 2.0 * vtkMath::Pi() * j / numSides;
                double sinPhi = sin(phi);
                double cosPhi = cos(phi);

                double x = centerX + radius * sinTheta1 * cosPhi;
                double y = centerY + radius * sinTheta1 * sinPhi;
                double z = centerZ + radius * cosTheta1;
                points->InsertNextPoint(x, y, z);
            }
        }

        for (int i = 0; i < numSegments; i++) {
            for (int j = 0; j < numSides; j++) {
                int p1 = i * numSides + j;
                int p2 = i * numSides + (j + 1) % numSides;
                int p3 = (i + 1) * numSides + j;
                int p4 = (i + 1) * numSides + (j + 1) % numSides;

                vtkLine* line1 = vtkLine::New();
                line1->GetPointIds()->SetId(0, p1);
                line1->GetPointIds()->SetId(1, p2);
                lines->InsertNextCell(line1);

                vtkLine* line2 = vtkLine::New();
                line2->GetPointIds()->SetId(0, p1);
                line2->GetPointIds()->SetId(1, p3);
                lines->InsertNextCell(line2);

                vtkLine* line3 = vtkLine::New();
                line3->GetPointIds()->SetId(0, p2);
                line3->GetPointIds()->SetId(1, p4);
                lines->InsertNextCell(line3);

                vtkLine* line4 = vtkLine::New();
                line4->GetPointIds()->SetId(0, p3);
                line4->GetPointIds()->SetId(1, p4);
                lines->InsertNextCell(line4);
            }
        }

        vtkPolyData* polyData = vtkPolyData::New();
        polyData->SetPoints(points);
        polyData->SetLines(lines);

        vtkPolyDataMapper* mapper = vtkPolyDataMapper::New();
        mapper->SetInputData(polyData);

        vtkActor* actor = vtkActor::New();
        actor->SetMapper(mapper);

        QColorDialog colorDialog;
        if (colorDialog.exec() == QDialog::Accepted) {
            QColor color = colorDialog.currentColor();
            int red = color.red();
            int green = color.green();
            int blue = color.blue();
            actor->GetProperty()->SetColor(red, green, blue);
        }

        double lineWidth = QInputDialog::getDouble(NULL, "Enter line width", "Line width", 1.0, 0.1, 10.0, 2);
        actor->GetProperty()->SetLineWidth(lineWidth);

        renderer->AddActor(actor);
        actors.push_back(actor);

        drawnshapes.insert("sphere " + QString::number(ISphere));
        ISphere++;


        renderer->ResetCamera();
        window->Render();
    }
    void drawCube(vtkRenderer* renderer, vtkGenericOpenGLRenderWindow* window, vtkTextActor* textActor) {
        double centerX = QInputDialog::getDouble(NULL, "Enter center coordinates", "x coordinate", 0, -1000, 1000, 2);
        double centerY = QInputDialog::getDouble(NULL, "Enter center coordinates", "y coordinate", 0, -1000, 1000, 2);
        double centerZ = QInputDialog::getDouble(NULL, "Enter center coordinates", "z coordinate", 0, -1000, 1000, 2);
        double sideLength = QInputDialog::getDouble(NULL, "Enter side length", "Side length", 1.0, 0.1, 100.0, 2);

        double halfLength = sideLength / 2.0;
        double xMin = centerX - halfLength;
        double xMax = centerX + halfLength;
        double yMin = centerY - halfLength;
        double yMax = centerY + halfLength;
        double zMin = centerZ - halfLength;
        double zMax = centerZ + halfLength;

        vtkPoints* points = vtkPoints::New();
        vtkCellArray* lines = vtkCellArray::New();

        // Define the vertices of the cube
        double vertices[8][3] = {
            {xMin, yMin, zMin},
            {xMax, yMin, zMin},
            {xMax, yMax, zMin},
            {xMin, yMax, zMin},
            {xMin, yMin, zMax},
            {xMax, yMin, zMax},
            {xMax, yMax, zMax},
            {xMin, yMax, zMax}
        };

        // Add the vertices to the points array
        for (int i = 0; i < 8; i++) {
            double* vertex = vertices[i];
            points->InsertNextPoint(vertex);
        }

        // Define the edges of the cube
        int edges[12][2] = {
            {0, 1}, {1, 2}, {2, 3}, {3, 0}, // Bottom face
            {4, 5}, {5, 6}, {6, 7}, {7, 4}, // Top face
            {0, 4}, {1, 5}, {2, 6}, {3, 7}  // Connecting edges
        };

        // Add the edges to the lines array
        for (int i = 0; i < 12; i++) {
            int* edge = edges[i];
            vtkLine* line = vtkLine::New();
            line->GetPointIds()->SetId(0, edge[0]);
            line->GetPointIds()->SetId(1, edge[1]);
            lines->InsertNextCell(line);
        }

        // Create the polydata and set the points and lines
        vtkPolyData* polyData = vtkPolyData::New();
        polyData->SetPoints(points);
        polyData->SetLines(lines);

        // Create the mapper and actor
        vtkPolyDataMapper* mapper = vtkPolyDataMapper::New();
        mapper->SetInputData(polyData);

        vtkActor* actor = vtkActor::New();
        actor->SetMapper(mapper);

        // Set color and line width
        QColorDialog colorDialog;
        if (colorDialog.exec() == QDialog::Accepted) {
            QColor color = colorDialog.currentColor();
            
            double red = color.redF();
            double green = color.greenF();
            double blue = color.blueF();
            actor->GetProperty()->SetColor(red, green, blue);
        }

        double lineWidth = QInputDialog::getDouble(NULL, "Enter line width", "Line width", 1.0, 0.1, 10.0, 2);
        actor->GetProperty()->SetLineWidth(lineWidth);

        // Add the actor to the renderer
        renderer->AddActor(actor);
        actors.push_back(actor);

        // Update the drawn shapes collection
        drawnshapes.insert("cube " + QString::number(ICube));
        ICube++;

        // Reset the camera and render the window
        renderer->ResetCamera();
        window->Render();
    }

    void drawEllipsoid(vtkRenderer* renderer, vtkGenericOpenGLRenderWindow* window, vtkTextActor* textActor) {
        double centerX = QInputDialog::getDouble(NULL, "Enter center coordinates", "x coordinate", 0, -1000, 1000, 2);
        double centerY = QInputDialog::getDouble(NULL, "Enter center coordinates", "y coordinate", 0, -1000, 1000, 2);
        double centerZ = QInputDialog::getDouble(NULL, "Enter center coordinates", "z coordinate", 0, -1000, 1000, 2);
        double radiusX = QInputDialog::getDouble(NULL, "Enter X-axis radius", "X-axis radius", 1.0, 0.1, 100.0, 2);
        double radiusY = QInputDialog::getDouble(NULL, "Enter Y-axis radius", "Y-axis radius", 1.0, 0.1, 100.0, 2);
        double radiusZ = QInputDialog::getDouble(NULL, "Enter Z-axis radius", "Z-axis radius", 1.0, 0.1, 100.0, 2);
        int numSides = 1000;
        int numSegments = 100;

        vtkPoints* points = vtkPoints::New();
        vtkCellArray* lines = vtkCellArray::New();

        for (int i = 0; i <= numSegments; i++) {
            double theta1 = vtkMath::Pi() * i / numSegments;
            double sinTheta1 = sin(theta1);
            double cosTheta1 = cos(theta1);

            for (int j = 0; j < numSides; j++) {
                double phi = 2.0 * vtkMath::Pi() * j / numSides;
                double sinPhi = sin(phi);
                double cosPhi = cos(phi);

                double x = centerX + radiusX * sinTheta1 * cosPhi;
                double y = centerY + radiusY * sinTheta1 * sinPhi;
                double z = centerZ + radiusZ * cosTheta1;
                points->InsertNextPoint(x, y, z);
            }
        }

        for (int i = 0; i < numSegments; i++) {
            for (int j = 0; j < numSides; j++) {
                int p1 = i * numSides + j;
                int p2 = i * numSides + (j + 1) % numSides;
                int p3 = (i + 1) * numSides + j;
                int p4 = (i + 1) * numSides + (j + 1) % numSides;

                vtkLine* line1 = vtkLine::New();
                line1->GetPointIds()->SetId(0, p1);
                line1->GetPointIds()->SetId(1, p2);
                lines->InsertNextCell(line1);

                vtkLine* line2 = vtkLine::New();
                line2->GetPointIds()->SetId(0, p1);
                line2->GetPointIds()->SetId(1, p3);
                lines->InsertNextCell(line2);

                vtkLine* line3 = vtkLine::New();
                line3->GetPointIds()->SetId(0, p2);
                line3->GetPointIds()->SetId(1, p4);
                lines->InsertNextCell(line3);

                vtkLine* line4 = vtkLine::New();
                line4->GetPointIds()->SetId(0, p3);
                line4->GetPointIds()->SetId(1, p4);
                lines->InsertNextCell(line4);
            }
        }

        vtkPolyData* polyData = vtkPolyData::New();
        polyData->SetPoints(points);
        polyData->SetLines(lines);

        vtkPolyDataMapper* mapper = vtkPolyDataMapper::New();
        mapper->SetInputData(polyData);

        vtkActor* actor = vtkActor::New();
        actor->SetMapper(mapper);

        QColorDialog colorDialog;
        if (colorDialog.exec() == QDialog::Accepted) {
            QColor color = colorDialog.currentColor();
            int red = color.red();
            int green = color.green();
            int blue = color.blue();
            actor->GetProperty()->SetColor(red, green, blue);
        }

        double lineWidth = QInputDialog::getDouble(NULL, "Enter line width", "Line width", 1.0, 0.1, 10.0, 2);
        actor->GetProperty()->SetLineWidth(lineWidth);

        renderer->AddActor(actor);
        actors.push_back(actor);

        drawnshapes.insert("ellipsoid " + QString::number(IEllipsoid));
        IEllipsoid++;

        renderer->ResetCamera();
        window->Render();
    }


    void drawHeart(vtkRenderer* renderer, vtkGenericOpenGLRenderWindow* window, vtkTextActor* textActor) {
        double centerX = QInputDialog::getDouble(NULL, "Enter center coordinates", "x coordinate", 0, -1000, 1000, 2);
        double centerY = QInputDialog::getDouble(NULL, "Enter center coordinates", "y coordinate", 0, -1000, 1000, 2);
        double width = QInputDialog::getDouble(NULL, "Enter width", "Width", 1.0, 0.1, 100.0, 2);

        int numSegments = 100;
        double segmentAngle = 2 * M_PI / numSegments;
        double radius = width / (2 * cos(segmentAngle / 2));

        vtkPoints* points = vtkPoints::New();
        vtkCellArray* lines = vtkCellArray::New();

        for (int i = 0; i <= numSegments; i++) {
            double angle = i * segmentAngle - M_PI;
            double x = centerX + radius * pow(sin(angle), 3);
            double y = centerY - radius * (13 * cos(angle) - 5 * cos(2 * angle) - 2 * cos(3 * angle) - cos(4 * angle)) / 16;
            points->InsertNextPoint(x, y, 0.0);

            if (i > 0) {
                vtkLine* line = vtkLine::New();
                line->GetPointIds()->SetId(0, i - 1);
                line->GetPointIds()->SetId(1, i);
                lines->InsertNextCell(line);
            }
        }

        vtkPolyData* polyData = vtkPolyData::New();
        polyData->SetPoints(points);
        polyData->SetLines(lines);

        vtkPolyDataMapper* mapper = vtkPolyDataMapper::New();
        mapper->SetInputData(polyData);

        vtkActor* actor = vtkActor::New();
        actor->SetMapper(mapper);

        QColorDialog colorDialog;
        if (colorDialog.exec() == QDialog::Accepted) {
            QColor color = colorDialog.currentColor();
            int red = color.red();
            int green = color.green();
            int blue = color.blue();
            actor->GetProperty()->SetColor(red, green, blue);
        }

        double lineWidth = QInputDialog::getDouble(NULL, "Enter line width", "Line width", 1.0, 0.1, 10.0, 2);
        actor->GetProperty()->SetLineWidth(lineWidth);
        drawnshapes.insert("Heart " + QString::number(IHeart));
        IHeart++;
        renderer->AddActor(actor);
        actors.push_back(actor);

        renderer->ResetCamera();
        window->Render();
    }

    void drawArc(vtkRenderer* renderer, vtkGenericOpenGLRenderWindow* window, vtkTextActor* textActor) {
        double centerX = QInputDialog::getDouble(NULL, "Enter center coordinates", "x coordinate", 0, -1000, 1000, 2);
        double centerY = QInputDialog::getDouble(NULL, "Enter center coordinates", "y coordinate", 0, -1000, 1000, 2);
        double radius = QInputDialog::getDouble(NULL, "Enter radius", "Radius", 1.0, 0.1, 100.0, 2);
        double startAngle = QInputDialog::getDouble(NULL, "Enter start angle", "Start angle (in degrees)", 0, -360, 360, 2);
        double endAngle = QInputDialog::getDouble(NULL, "Enter end angle", "End angle (in degrees)", 90, -360, 360, 2);

        int numSegments = 100;
        double segmentAngle = (endAngle - startAngle) / numSegments;

        vtkPoints* points = vtkPoints::New();
        vtkCellArray* lines = vtkCellArray::New();
        for (int i = 0; i <= numSegments; i++) {
            double angle = vtkMath::RadiansFromDegrees(startAngle + i * segmentAngle);
            double x = centerX + radius * cos(angle);
            double y = centerY + radius * sin(angle);
            points->InsertNextPoint(x, y, 0.0);

            if (i > 0) {
                vtkLine* line = vtkLine::New();
                line->GetPointIds()->SetId(0, i - 1);
                line->GetPointIds()->SetId(1, i);
                lines->InsertNextCell(line);
            }
        }

        vtkPolyData* polyData = vtkPolyData::New();
        polyData->SetPoints(points);
        polyData->SetLines(lines);

        vtkPolyDataMapper* mapper = vtkPolyDataMapper::New();
        mapper->SetInputData(polyData);

        vtkActor* actor = vtkActor::New();
        actor->SetMapper(mapper);

        QColorDialog colorDialog;
        if (colorDialog.exec() == QDialog::Accepted) {
            QColor color = colorDialog.currentColor();
            int red = color.red();
            int green = color.green();
            int blue = color.blue();
            actor->GetProperty()->SetColor(red, green, blue);
        }

        double lineWidth = QInputDialog::getDouble(NULL, "Enter line width", "Line width", 1.0, 0.1, 10.0, 2);
        actor->GetProperty()->SetLineWidth(lineWidth);
        drawnshapes.insert("Arc " + QString::number(IArc));
        IArc++;
        renderer->AddActor(actor);
        actors.push_back(actor);

        renderer->ResetCamera();
        window->Render();
    }
    void drawEllipse(vtkRenderer* renderer, vtkGenericOpenGLRenderWindow* window, vtkTextActor* textActor) {
        double centerX = QInputDialog::getDouble(NULL, "Enter center coordinates", "x coordinate", 0, -1000, 1000, 2);
        double centerY = QInputDialog::getDouble(NULL, "Enter center coordinates", "y coordinate", 0, -1000, 1000, 2);
        double semiAxisX = QInputDialog::getDouble(NULL, "Enter semi-axis lengths", "Semi-axis length along x", 1.0, 0.1, 100.0, 2);
        double semiAxisY = QInputDialog::getDouble(NULL, "Enter semi-axis lengths", "Semi-axis length along y", 1.0, 0.1, 100.0, 2);
        double startAngle = QInputDialog::getDouble(NULL, "Enter start angle", "Start angle (in degrees)", 0, -360, 360, 2);
        double endAngle = QInputDialog::getDouble(NULL, "Enter end angle", "End angle (in degrees)", 360, -360, 360, 2);

        int numSegments = 100;
        double segmentAngle = (endAngle - startAngle) / numSegments;

        vtkPoints* points = vtkPoints::New();
        vtkCellArray* lines = vtkCellArray::New();
        for (int i = 0; i <= numSegments; i++) {
            double angle = vtkMath::RadiansFromDegrees(startAngle + i * segmentAngle);
            double x = centerX + semiAxisX * cos(angle);
            double y = centerY + semiAxisY * sin(angle);
            points->InsertNextPoint(x, y, 0.0);

            if (i > 0) {
                vtkLine* line = vtkLine::New();
                line->GetPointIds()->SetId(0, i - 1);
                line->GetPointIds()->SetId(1, i);
                lines->InsertNextCell(line);
            }
        }

        vtkPolyData* polyData = vtkPolyData::New();
        polyData->SetPoints(points);
        polyData->SetLines(lines);

        vtkPolyDataMapper* mapper = vtkPolyDataMapper::New();
        mapper->SetInputData(polyData);

        vtkActor* actor = vtkActor::New();
        actor->SetMapper(mapper);

        QColorDialog colorDialog;
        if (colorDialog.exec() == QDialog::Accepted) {
            QColor color = colorDialog.currentColor();
            int red = color.red();
            int green = color.green();
            int blue = color.blue();
            actor->GetProperty()->SetColor(red, green, blue);

            actor->GetProperty()->SetOpacity(0.5); // set ellipse opacity

        }

        double lineWidth = QInputDialog::getDouble(NULL, "Enter line width", "Line width", 1.0, 0.1, 10.0, 2);
        actor->GetProperty()->SetLineWidth(lineWidth);
        drawnshapes.insert("Ellipse " + QString::number(IEllipse));
        IEllipse++;
        renderer->AddActor(actor);
        actors.push_back(actor);
        renderer->ResetCamera();
        window->Render();
    }

    void selectLine(int index) {
        if (index >= 0 && index < lineActors.size()) {
            vtkActor* lineActor = lineActors[index];
            lineActor->GetProperty()->SetColor(1.0, 1.0, 1.0); // Set line color to white
        }
    }


    void setSecondCoordinate(vtkLineSource* linesource, vtkGenericOpenGLRenderWindow* window, vtkTextActor* TextActor, vtkActor* lineActor) {
        double x2 = QInputDialog::getDouble(NULL, "Enter second coordinates", "x2 coordinate", 0, -1000, 1000, 2);
        double y2 = QInputDialog::getDouble(NULL, "Enter second coordinates", "y2 coordinate", 0, -1000, 1000, 2);
        linesource->SetPoint2(x2, y2, 0.0);
        updateTextCoordinates(linesource, TextActor, lineActor);
        window->Render();
    }

    void readInputFile(vtkRenderer* renderer, vtkGenericOpenGLRenderWindow* window, vtkTextActor* textActor) {
        QString fileName = QFileDialog::getOpenFileName(nullptr, "Open File", ".", "Text Files (*.txt)");
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QString line;

            while (!in.atEnd()) {
                line = in.readLine();

                if (line.startsWith("L")) {
                    QStringList data = line.split(' ');
                    double point1X = data[1].toDouble();
                    double point1Y = data[2].toDouble();
                    double point2X = data[3].toDouble();
                    double point2Y = data[4].toDouble();
                    double colorR = data[5].toDouble();
                    double colorG = data[6].toDouble();
                    double colorB = data[7].toDouble();
                    double lineWidth = data[8].toDouble();
                    drawLineee(renderer, window, textActor, point1X, point1Y, point2X, point2Y, colorR, colorG, colorB, lineWidth);
                    // Process line data (e.g., create line object)
                }
                else if (line.startsWith("P")) {
                    QStringList data = line.split(' ');
                    int numPoints = data[1].toInt();

                    QVector<double*> polygonPoints;
                    for (int i = 0; i < numPoints; i++) {
                        double* point = new double[2];
                        point[0] = data[2 + i * 2].toDouble();
                        point[1] = data[3 + i * 2].toDouble();
                        polygonPoints.push_back(point);
                    }

                    double colorR = data[2 + numPoints * 2].toDouble();
                    double colorG = data[3 + numPoints * 2].toDouble();
                    double colorB = data[4 + numPoints * 2].toDouble();
                    double lineWidth = data[5 + numPoints * 2].toDouble();

                    // Process polygon data (e.g., create polygon object)
                }
                else if (line.startsWith("c")) {
                    QStringList data = line.split(' ');
                    
                    double point1X = data[1].toDouble();
                    double point1Y = data[2].toDouble();
                    double radius = data[3].toDouble();
                    
                    double colorR = data[4].toDouble();
                    double colorG = data[5].toDouble();
                    double colorB = data[6].toDouble();
                    double lineWidth = data[7].toDouble();
                    
               
                     drawCircleread(renderer, window, textActor, point1X, point1Y, radius, colorR, colorG, colorB, lineWidth);

                }
            }

            file.close();
        }
    }

    void openColorWindow(vtkGenericOpenGLRenderWindow* window, vtkActor* lineActor) {
        QColorDialog colorDialog;
        if (colorDialog.exec() == QDialog::Accepted) {
            QColor color = colorDialog.currentColor();
            int red = color.red();
            int green = color.green();
            int blue = color.blue();
            lineActor->GetProperty()->SetColor(red, green, blue);
            window->Render();
        }
    }

    //void changeLineProperty(int index, vtkGenericOpenGLRenderWindow* window, vtkActor* lineActor) {
    //    cout<<lineActor->GetProperty()->GetLineStipplePattern();
    //    if (index == 0) {
    //        lineActor->GetProperty()->SetLineStipplePattern(65535);
    //        lineActor->GetProperty()->SetLineStippleRepeatFactor(1);
    //        //window->Render();
    //    }
    //    else if (index == 1) {//dashed
    //        lineActor->GetProperty()->SetLineStipplePattern(255); 
    //        lineActor->GetProperty()->SetLineStippleRepeatFactor(1);
    //        //window->Render();
    //    }
    //    else if (index == 2) {//dotted
    //        lineActor->GetProperty()->SetLineStipplePattern(43690);
    //        lineActor->GetProperty()->SetLineStippleRepeatFactor(1);
    //        //window->Render();
    //    }
    //}

    void changeLineWidth(int value, vtkGenericOpenGLRenderWindow* window, vtkActor* lineActor) {
        lineActor->GetProperty()->SetLineWidth(value);
        window->Render();
    }

    void drawShapeWithColor(vtkRenderer* renderer, vtkGenericOpenGLRenderWindow* window) {




        // Create a drop-down list dialog box
        bool ok;
        QString shapeName = QInputDialog::getItem(NULL, "Select a shape to change color", "Shapes:", QStringList(drawnshapes.begin(), drawnshapes.end()), 0, false, &ok);
        if (!ok) {
            return;
        }
        
        // Find the selected shape and change its color to black
        int shapeIndex = shapeName.split(" ")[1].toInt();
        
        QString parts = shapeName.split(" ")[0];
        int shapeIndex = drawnshapes.indexOf(shapeName);
        actors[shapeIndex]->GetProperty()->SetColor(0, 0, 0);
        
        actors.erase(actors.begin() + shapeIndex);
       
        drawnshapes.erase(shapeName);
        
        if (parts == "Line") {
            ILine--;
        }
        else if (parts == "Circle") {
            ICircle--;
         /* if (circleData.find(shapeIndex) != circleData.end()) {
                circleData[shapeIndex][8] = "d";
            }*/ if (shapeIndex >= 0 && shapeIndex < circleData.size()) {
            // Erase the element at shapeIndex and shift the remaining elements
                auto it = circleData.begin();
                std::advance(it, shapeIndex);
                circleData.erase(it);
            }
            wCircle--;

        }
        else if (parts == "Arc") {
            IArc--;
        }
        else if (parts == "Ellipse") {
            IEllipse--;
        }
        else if (parts == "Polygon") {
            IPolygon--;
        }
        else if (parts == "Heart") {
            IHeart--;
        }
        else if (parts == "Star") {
            IStar--;
        }
        else if (parts == "Right Polygon") {
            IRight--;
        }
        else if (parts == "Sphere")
        {
            ISphere--;
        }
        else if (parts == "cube")
        {
            ICube--;
        }
        else if (parts == "ellipsoid")
        {
            IEllipsoid--;
        }




        // Render the updated scene
        renderer->ResetCamera();
        window->Render();
    }
    void drawShapeWithColor3D(vtkRenderer* renderer, vtkGenericOpenGLRenderWindow* window) {
        // Create a drop-down list dialog box
        bool ok;
        QString shapeName = QInputDialog::getItem(NULL, "Select a shape to change color", "Shapes:", QStringList(drawnshapes.begin(), drawnshapes.end()), 0, false, &ok);
        if (!ok) {
            return;
        }

        // Find the selected shape and change its color to black
        int shapeIndex = shapeName.split(" ")[1].toInt();
        QString parts = shapeName.split(" ")[0];

        // Remove the selected shape from the renderer
        renderer->RemoveActor(actors[shapeIndex]);
        actors.erase(actors.begin() + shapeIndex);
        drawnshapes.erase(shapeName);

        if (parts == "Sphere") {
            ISphere--;
        }
        
        if (parts == "Cube") {
            ICube--;
        }
        if (parts == "Cube") {
            IEllipsoid--;
        }
        // Update the scene and render
        renderer->ResetCamera();
        window->Render();
    }






    void drawShapeScaled(vtkRenderer* renderer, vtkGenericOpenGLRenderWindow* window) {



        // Create a drop-down list dialog box
        bool ok;
        QString shapeName = QInputDialog::getItem(NULL, "Select a shape to change color", "Shapes:", QStringList(drawnshapes.begin(), drawnshapes.end()), 0, false, &ok);
        if (!ok) {
            return;
        }
        if (shapeName.contains("cube") || shapeName.contains("ellipsoid") || shapeName.contains("sphere"))
        {
            // Ask the user for the scaling factors along x, y, and z axes
            bool ok2;
            double scaleX = QInputDialog::getDouble(NULL, "Enter scaling factor for X axis", "Scaling factor for X axis:", 1.0, 0.0, 100.0, 2, &ok2);
            if (!ok2) {
                return;
            }

            double scaleY = QInputDialog::getDouble(NULL, "Enter scaling factor for Y axis", "Scaling factor for Y axis:", 1.0, 0.0, 100.0, 2, &ok2);
            if (!ok2) {
                return;
            }

            double scaleZ = QInputDialog::getDouble(NULL, "Enter scaling factor for Z axis", "Scaling factor for Z axis:", 1.0, 0.0, 100.0, 2, &ok2);
            if (!ok2) {
                return;
            }

            // Find the selected shape and scale it by the user-specified factors
            int shapeIndex = shapeName.split(" ")[1].toInt();
            vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
            transform->Scale(scaleX, scaleY, scaleZ);
            actors[shapeIndex]->SetUserTransform(transform);

            // Render the updated scene
            renderer->ResetCamera();
            window->Render();

        }
        else {
            // Ask the user for the scaling factor
            bool ok2;
            double scalingFactor = QInputDialog::getDouble(NULL, "Enter scaling factor", "Scaling factor:", 1.0, 0.0, 100.0, 2, &ok2);
            if (!ok2) {
                return;
            }

            // Find the selected shape and scale it by the user-specified factor
            int shapeIndex = shapeName.split(" ")[1].toInt();
            vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
            transform->Scale(scalingFactor, scalingFactor, scalingFactor);
            actors[shapeIndex]->SetUserTransform(transform);

            // Render the updated scene
            renderer->ResetCamera();
            window->Render();
        }
    }


    void drawShapeSheared(vtkRenderer* renderer, vtkGenericOpenGLRenderWindow* window) {


        // Create a drop-down list dialog box
        bool ok;
        QString shapeName = QInputDialog::getItem(NULL, "Select a shape to change color", "Shapes:", QStringList(drawnshapes.begin(), drawnshapes.end()), 0, false, &ok);
        if (!ok) {
            return;
        }
        if (shapeName.contains("cube") || shapeName.contains("ellipsoid") || shapeName.contains("sphere"))
        {
            // Ask the user for the shearing factors along each axis
            bool okX, okY, okZ;
            double shearingFactorX = QInputDialog::getDouble(NULL, "Enter shearing factor for X-axis", "Shearing factor for X-axis:", 0.0, -100.0, 100.0, 2, &okX);
            double shearingFactorY = QInputDialog::getDouble(NULL, "Enter shearing factor for Y-axis", "Shearing factor for Y-axis:", 0.0, -100.0, 100.0, 2, &okY);
            double shearingFactorZ = QInputDialog::getDouble(NULL, "Enter shearing factor for Z-axis", "Shearing factor for Z-axis:", 0.0, -100.0, 100.0, 2, &okZ);
            if (!okX || !okY || !okZ) {
                return;
            }

            // Create a transform and set its matrix based on the shearing factors
            vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
            vtkSmartPointer<vtkMatrix4x4> matrix = vtkSmartPointer<vtkMatrix4x4>::New();
            matrix->Identity();
            matrix->SetElement(0, 1, shearingFactorX);
            matrix->SetElement(0, 2, shearingFactorY);
            matrix->SetElement(0, 3, shearingFactorZ);
            transform->SetMatrix(matrix);
            // Get the selected shape and apply the transform
            vtkActor* actor = actors[shapeName.toInt()];
            actor->SetUserTransform(transform);
            actor->Modified();
            // Render the updated scene
            renderer->ResetCamera();
            window->Render();

        }
        else
        {


            // Ask the user for the shearing factor
            bool ok2;
            double shearingFactor = QInputDialog::getDouble(NULL, "Enter shearing factor", "Shearing factor:", 0.0, -100.0, 100.0, 2, &ok2);
            if (!ok2) {
                return;
            }

            // Create a transform and set its matrix based on the shearing factor
            vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
            vtkSmartPointer<vtkMatrix4x4> matrix = vtkSmartPointer<vtkMatrix4x4>::New();
            matrix->Identity();
            matrix->SetElement(0, 1, shearingFactor);
            transform->SetMatrix(matrix);

            // Get the selected shape and apply the transform
            vtkActor* actor = actors[shapeName.toInt()];
            actor->SetUserTransform(transform);
            actor->Modified();
            // Render the updated scene
            renderer->ResetCamera();
            window->Render();
        }

    }



    void rotateShape(vtkRenderer* renderer, vtkGenericOpenGLRenderWindow* window) {



        // Create a drop-down list dialog box
        bool ok;
        QString shapeName = QInputDialog::getItem(NULL, "Select a shape to change color", "Shapes:", QStringList(drawnshapes.begin(), drawnshapes.end()), 0, false, &ok);
        if (!ok) {
            return;
        }
        if (shapeName.contains("cube") || shapeName.contains("ellipsoid") || shapeName.contains("sphere"))
        {
            // Get the rotation angles from the user for each axis
            double angleX = QInputDialog::getDouble(NULL, "Rotate Shape", "Enter rotation angle around X-axis in degrees:", 0, -360, 360, 1, &ok);
            if (!ok) {
                return;
            }
            double angleY = QInputDialog::getDouble(NULL, "Rotate Shape", "Enter rotation angle around Y-axis in degrees:", 0, -360, 360, 1, &ok);
            if (!ok) {
                return;
            }
            double angleZ = QInputDialog::getDouble(NULL, "Rotate Shape", "Enter rotation angle around Z-axis in degrees:", 0, -360, 360, 1, &ok);
            if (!ok) {
                return;
            }

            // Find the selected shape and rotate it
            int shapeIndex = shapeName.split(" ")[1].toInt();
            vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
            transform->RotateX(angleX);
            transform->RotateY(angleY);
            transform->RotateZ(angleZ);
            actors[shapeIndex]->SetUserTransform(transform);

            // Render the updated scene
            renderer->ResetCamera();
            window->Render();
        }

        else
        {
            // Get the rotation angle from the user
            double angle = QInputDialog::getDouble(NULL, "Rotate Shape", "Enter rotation angle in degrees:", 0, -360, 360, 1, &ok);
            if (!ok) {
                return;
            }

            // Find the selected shape and rotate it
            int shapeIndex = shapeName.split(" ")[1].toInt();
            vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
            transform->RotateZ(angle);
            actors[shapeIndex]->SetUserTransform(transform);

            // Render the updated scene
            renderer->ResetCamera();
            window->Render();
        }

    }




    void translateShape(vtkRenderer* renderer, vtkGenericOpenGLRenderWindow* window) {



        // Create a drop-down list dialog box
        bool ok;
        QString shapeName = QInputDialog::getItem(NULL, "Select a shape to change color", "Shapes:", QStringList(drawnshapes.begin(), drawnshapes.end()), 0, false, &ok);
        if (!ok) {
            return;
        }
        if (shapeName.contains("cube") || shapeName.contains("ellipsoid") || shapeName.contains("sphere"))
        {
            // Get the rotation angles from the user for each axis
            double angleX = QInputDialog::getDouble(NULL, "Rotate Shape", "Enter rotation angle around X-axis in degrees:", 0, -360, 360, 1, &ok);
            if (!ok) {
                return;
            }
            double angleY = QInputDialog::getDouble(NULL, "Rotate Shape", "Enter rotation angle around Y-axis in degrees:", 0, -360, 360, 1, &ok);
            if (!ok) {
                return;
            }
            double angleZ = QInputDialog::getDouble(NULL, "Rotate Shape", "Enter rotation angle around Z-axis in degrees:", 0, -360, 360, 1, &ok);
            if (!ok) {
                return;
            }

            // Find the selected shape and rotate it
            int shapeIndex = shapeName.split(" ")[1].toInt();
            vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
            transform->RotateX(angleX);
            transform->RotateY(angleY);
            transform->RotateZ(angleZ);
            actors[shapeIndex]->SetUserTransform(transform);

            // Render the updated scene
            renderer->ResetCamera();
            window->Render();
        }
        else {
            // Find the selected shape and get its current position
            int shapeIndex = shapeName.split(" ")[1].toInt();
            double currentPosition[3];
            actors[shapeIndex]->GetPosition(currentPosition);

            // Create input dialogs to get the translation values from the user
            bool ok1, ok2;
            double horizontalTranslation = QInputDialog::getDouble(NULL, "Horizontal translation", "Enter the horizontal translation value:", 0, -100000, 100000, 2, &ok1);
            double verticalTranslation = QInputDialog::getDouble(NULL, "Vertical translation", "Enter the vertical translation value:", 0, -100000, 100000, 2, &ok2);
            if (!ok1 || !ok2) {
                return;
            }

            // Calculate the new position of the selected shape based on the translation values
            double newPosition[3] = { currentPosition[0] + horizontalTranslation, currentPosition[1] + verticalTranslation, currentPosition[2] };

            // Set the new position of the selected shape
            actors[shapeIndex]->SetPosition(newPosition);

            // Render the updated scene
            renderer->ResetCamera();
            window->Render();
        }
    }



} // namespace


int main(int argc, char** argv)
{
    QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());

    QApplication app(argc, argv);

    // main window
    QMainWindow mainWindow;
    mainWindow.resize(1200, 900);

    // control area
    QDockWidget controlDock;
    mainWindow.addDockWidget(Qt::LeftDockWidgetArea, &controlDock);

    QLabel controlDockTitle("Control Dock");
    controlDockTitle.setMargin(20);
    controlDock.setTitleBarWidget(&controlDockTitle);

    QPointer<QVBoxLayout> dockLayout = new QVBoxLayout();
    QWidget layoutContainer;
    layoutContainer.setLayout(dockLayout);
    controlDock.setWidget(&layoutContainer);
    QScrollArea scrollArea;
    scrollArea.setWidgetResizable(true); // Enable widget resizing
    scrollArea.setWidget(&layoutContainer); // Set the layout container as the widget

    controlDock.setWidget(&scrollArea); // Add the scroll area to the control dock

    QPushButton drawLine;
    drawLine.setText("Draw Line");
    dockLayout->addWidget(&drawLine, 0, Qt::AlignTop);
    // create a new QComboBox
    QComboBox lineComboBox;

    QPushButton delt;
    delt.setText("Delete");
    dockLayout->addWidget(&delt, 0, Qt::AlignTop);

    QPushButton scale;
    scale.setText("Scale");
    dockLayout->addWidget(&scale, 0, Qt::AlignTop);

    QPushButton shear;
    shear.setText("Shearing");
    dockLayout->addWidget(&shear, 0, Qt::AlignTop);

    QPushButton rotate;
    rotate.setText("Rotate");
    dockLayout->addWidget(&rotate, 0, Qt::AlignTop);

    QPushButton translate;
    translate.setText("Translate");
    dockLayout->addWidget(&translate, 0, Qt::AlignTop);
    QPushButton setRightPolygon;
    setRightPolygon.setText("Draw Right polygon");
    dockLayout->addWidget(&setRightPolygon, 1, Qt::AlignTop);
    QPushButton setcircle;
    setcircle.setText("Draw circle");
    dockLayout->addWidget(&setcircle, 1, Qt::AlignTop);
    QPushButton setSphere;
    setSphere.setText("Draw sphere");
    dockLayout->addWidget(&setSphere, 1, Qt::AlignTop);
    QPushButton setCube;
    setCube.setText("Draw Cube");
    dockLayout->addWidget(&setCube, 1, Qt::AlignTop);

    QPushButton setEllipsoid;
    setEllipsoid.setText("Draw Ellipsoid");
    dockLayout->addWidget(&setEllipsoid, 1, Qt::AlignTop);
    QPushButton setdrawArc;
    setdrawArc.setText("Draw Arc");
    dockLayout->addWidget(&setdrawArc, 1, Qt::AlignTop);

    QPushButton setdrawHeart;
    setdrawHeart.setText("Draw Heart");
    dockLayout->addWidget(&setdrawHeart, 1, Qt::AlignTop);


    QPushButton setdrawPolgn;
    setdrawPolgn.setText("Draw Polygon");
    dockLayout->addWidget(&setdrawPolgn, 1, Qt::AlignTop);

    QPushButton setdrawStar;
    setdrawStar.setText("Draw Star");
    dockLayout->addWidget(&setdrawStar, 1, Qt::AlignTop);

    QPushButton setdrawEllipse;
    setdrawEllipse.setText("Draw Ellipse");
    dockLayout->addWidget(&setdrawEllipse, 1, Qt::AlignTop);

    QPushButton readFile;
    readFile.setText("Read Input File");
    dockLayout->addWidget(&readFile, 0, Qt::AlignTop);

    QPushButton writeFile;
    writeFile.setText("Write Input File");
    dockLayout->addWidget(&writeFile, 1, Qt::AlignTop);



    QSlider slider;
    slider.setMinimum(0);
    slider.setMaximum(20);
    slider.setValue(0);
    slider.setOrientation(Qt::Horizontal);
    dockLayout->addWidget(&slider, 1, Qt::AlignTop);

    /*QComboBox comboBox ;
    comboBox.addItem(QApplication::tr("solid"));
    comboBox.addItem(QApplication::tr("dashed"));
    comboBox.addItem(QApplication::tr("dotted"));
    dockLayout->addWidget(&comboBox, 1, Qt::AlignTop);*/

    //render area
    QPointer<QVTKOpenGLNativeWidget> vtkRenderWidget = new QVTKOpenGLNativeWidget();
    mainWindow.setCentralWidget(vtkRenderWidget);
    mainWindow.setWindowTitle("VTK Line Example");



    // VTK part
    vtkNew<vtkGenericOpenGLRenderWindow> window;
    vtkRenderWidget->setRenderWindow(window);

    vtkNew<vtkLineSource> linesource;
    vtkNew<vtkPolyDataMapper> linemapper;
    linemapper->SetInputConnection(linesource->GetOutputPort());

    vtkNew<vtkActor> lineactor;
    lineactor->SetMapper(linemapper);

    vtkNew<vtkRenderer> renderer;
    renderer->AddActor(lineactor);
    window->AddRenderer(renderer);

    vtkNew<vtkPointPicker> pointPicker;
    window->SetInteractor(vtkRenderWidget->interactor());
    window->GetInteractor()->SetPicker(pointPicker);

    /* vtkNew<customMouseInteractorStyle> style;
     style->setLineSource(linesource);
     style->setVTKActor(lineactor);

     window->GetInteractor()->SetInteractorStyle(style);

     vtkNew<vtkTextActor> textActor;
     textActor->SetInput("Line coordinates: (0, 0) - (0, 0)");
     textActor->GetTextProperty()->SetColor(1.0, 0.0, 0.0);
     textActor->GetTextProperty()->SetFontSize(40);
     style->setTextActor(textActor);*/
    vtkNew<vtkTextActor> textActor;
    renderer->AddActor(textActor);

    vtkNew<vtkTextRepresentation> textRepresentation;
    textRepresentation->GetPositionCoordinate()->SetValue(0.15, 0.15);
    textRepresentation->GetPosition2Coordinate()->SetValue(0.7, 0.2);

    vtkNew<vtkTextWidget> textWidget;
    textWidget->SetRepresentation(textRepresentation);
    textWidget->SelectableOff();
    textWidget->SetInteractor(vtkRenderWidget->interactor());


    //// connect the buttons
    QObject::connect(&drawLine, &QPushButton::released,
        [&]() { ::drawLine(renderer, window, textActor, lineComboBox); });




    QObject::connect(&setdrawEllipse, &QPushButton::released,
        [&]() { ::drawEllipse(renderer, window, textActor); });
    // connect the combo box signal to a slot
    QObject::connect(&lineComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [&](int index) {
        // Do something with the selected line
        vtkActor* selectedActor = lineActors[index];
        // for example, change the line color to red
        selectedActor->GetProperty()->SetColor(1.0, 0.0, 0.0);
        });



    QObject::connect(&setRightPolygon, &QPushButton::released,
        [&]() { ::drawPolygon(renderer, window, textActor); });


    QObject::connect(&setdrawStar, &QPushButton::released,
        [&]() { ::drawStar(renderer, window, textActor); });



    QObject::connect(&setdrawHeart, &QPushButton::released,
        [&]() { ::drawHeart(renderer, window, textActor); });
    QObject::connect(&setdrawPolgn, &QPushButton::released,
        [&]() { ::drawPolgn(renderer, window, textActor); });

    QObject::connect(&setcircle, &QPushButton::released,
        [&]() { ::drawCircle(renderer, window, textActor); });

    QObject::connect(&setSphere, &QPushButton::released,
        [&]() { ::drawSphere(renderer, window, textActor); });


    QObject::connect(&setEllipsoid, &QPushButton::released,
        [&]() { ::drawEllipsoid(renderer, window, textActor); });

    QObject::connect(&setCube, &QPushButton::released,
        [&]() { ::drawCube(renderer, window, textActor); });
    QObject::connect(&setdrawArc, &QPushButton::released,
        [&]() { ::drawArc(renderer, window, textActor); });
    QObject::connect(&readFile, &QPushButton::released,
        [&]() { ::readInputFile(renderer, window, textActor); });

    QObject::connect(&writeFile, &QPushButton::released,
        [&]() { ::writeInFile(); });



    QObject::connect(&delt, &QPushButton::released,
        [&]() { ::drawShapeWithColor(renderer, window); });


    QObject::connect(&scale, &QPushButton::released,
        [&]() { ::drawShapeScaled(renderer, window); });
    QObject::connect(&shear, &QPushButton::released,
        [&]() { ::drawShapeSheared(renderer, window); });
    QObject::connect(&rotate, &QPushButton::released,
        [&]() { ::rotateShape(renderer, window); });
    QObject::connect(&translate, &QPushButton::released,
        [&]() { ::translateShape(renderer, window); });


    /*QObject::connect(&comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [&](int index) {
        ::changeLineProperty(index,window,lineactor);
        drawShapeWithColor(vtkRenderer* renderer, vtkGenericOpenGLRenderWindow* window, vtkTextActor* textActor)
        });*/

    QObject::connect(&slider, &QSlider::valueChanged, [&](int value) {
        // Do something with the value
        ::changeLineWidth(value, window, lineactor);
        });


    mainWindow.show();

    return app.exec();
}