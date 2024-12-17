const express = require('express');
const { spawn } = require('child_process');
const fs = require('fs'); // File system module
const cors = require('cors');  
const path = require('path'); // Path module for handling file paths
const app = express();
const port = 3001;

app.use(cors());  
app.use(express.json());  

app.post('/process-dna', (req, res) => {
    const dnaSequence = req.body.dnaSequence;

    if (!dnaSequence) {
        return res.status(400).send('DNA sequence is required');
    }

    console.log('Received DNA sequence:', dnaSequence);

    // Step 1: Create a .fasta file
    const uploadsDir = path.join(__dirname, 'uploads');
    if (!fs.existsSync(uploadsDir)) {
        fs.mkdirSync(uploadsDir); // Create uploads directory if it doesn't exist
    }

    const fileName = `dna_${Date.now()}.fasta`; // Unique file name
    const filePath = path.join(uploadsDir, fileName);

    // Write the DNA sequence to the file in FASTA format
    const fastaContent = `>DNA_sequence\n${dnaSequence}`;
    fs.writeFileSync(filePath, fastaContent, 'utf8');

    console.log('FASTA file created at:', filePath);

    // Step 2: Pass the file path to the C++ executable
    const executablePath = './execute.exe'; // Path to your C++ executable
    const process = spawn(executablePath, [filePath]); // Pass file path as an argument

    let output = '';
    process.stdout.on('data', (data) => {
        output += data.toString();
    });

    let errorOutput = '';
    process.stderr.on('data', (data) => {
        errorOutput += data.toString();
    });

    process.on('close', (code) => {
        // Step 3: Clean up the file after processing
       

        if (code !== 0) {
            console.error(`Error executing C++ program: ${errorOutput}`);
            return res.status(500).send('Error processing DNA sequence');
        }

        console.log('Processed DNA:', output.trim());
        return res.json({ processedDna: output.trim() });
    });
});

app.listen(port, () => {
    console.log(`Server running at http://localhost:${port}`);
});
